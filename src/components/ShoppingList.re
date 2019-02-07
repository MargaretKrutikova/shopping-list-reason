open Api;
open Utils;
open Types;

type state = {
  shoppingList,
  isLoading: bool,
  error: option(string),
};

type shoppingItemProperty =
  | Product
  | Note;

type action =
  | ShoppingListFetch
  | ShoppingListFetchSuccess(shoppingList)
  | ShoppingListFetchError
  | AddShoppingItem
  | ChangeShoppingItemProperty(int, string, shoppingItemProperty);

let component = ReasonReact.reducerComponent("ShoppingList");

let make = _children => {
  let updateItems = (state: state, items: array(shoppingItem)) => {
    ...state,
    shoppingList: {
      ...state.shoppingList,
      items,
    },
  };
  {
    ...component,

    initialState: () => {
      isLoading: false,
      error: None,
      shoppingList: {
        name: "",
        status: "",
        items: [||],
      },
    },

    didMount: self => self.send(ShoppingListFetch),

    reducer: (action, state) =>
      switch (action) {
      | ShoppingListFetch =>
        ReasonReact.UpdateWithSideEffects(
          {...state, isLoading: true},
          self =>
            Js.Promise.(
              getShoppingList()
              |> then_(result =>
                   switch (result) {
                   | Success(list) =>
                     self.send(ShoppingListFetchSuccess(list)) |> resolve
                   | Error => self.send(ShoppingListFetchError) |> resolve
                   }
                 )
              |> ignore
            ),
        )

      | ShoppingListFetchSuccess(list) =>
        ReasonReact.Update({...state, isLoading: false, shoppingList: list})

      | ShoppingListFetchError =>
        ReasonReact.Update({
          ...state,
          isLoading: false,
          error: Some("Failed to fetch shopping list"),
        })

      | AddShoppingItem =>
        let newItem: shoppingItem = {product: "", note: "", assignee: None};

        let items = Array.append(state.shoppingList.items, [|newItem|]);
        ReasonReact.Update(updateItems(state, items));

      | ChangeShoppingItemProperty(index, newValue, property) =>
        let updateFn =
          switch (property) {
          | Product => (item => {...item, product: newValue})
          | Note => (item => {...item, note: newValue})
          };

        let items =
          updateWithIndex(state.shoppingList.items, updateFn, index);
        ReasonReact.Update(updateItems(state, items));
      },

    render: self =>
      <div>
        {self.state.isLoading ?
           <span> {ReasonReact.string("...Loading")} </span> :
           ReasonReact.null}
        {self.state.shoppingList.items
         ->Belt.Array.mapWithIndex((index, item) =>
             <div key={string_of_int(index)}>
               <input
                 placeholder="Name"
                 value={item.product}
                 onChange={event =>
                   self.send(
                     ChangeShoppingItemProperty(
                       index,
                       ReactEvent.Form.target(event)##value,
                       Product,
                     ),
                   )
                 }
               />
               <input
                 placeholder="Note"
                 value={item.note}
                 onChange={event =>
                   self.send(
                     ChangeShoppingItemProperty(
                       index,
                       ReactEvent.Form.target(event)##value,
                       Note,
                     ),
                   )
                 }
               />
             </div>
           )
         |> ReasonReact.array}
        <button onClick={_event => self.send(AddShoppingItem)}>
          {ReasonReact.string("Add shopping item")}
        </button>
      </div>,
  };
};
