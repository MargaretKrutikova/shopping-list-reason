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
  | ChangeShoppingItem(int, shoppingItem);

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

      | ChangeShoppingItem(index, newItem) =>
        let updateFn = _item => newItem;

        let items =
          updateWithIndex(state.shoppingList.items, updateFn, index);
        ReasonReact.Update(updateItems(state, items));
      },

    render: self =>
      <>
        <h1> {ReasonReact.string("Shopping List")} </h1>
        {self.state.isLoading ?
           <span> {ReasonReact.string("...Loading")} </span> :
           ReasonReact.null}
        <ShoppingList
          list={self.state.shoppingList}
          onItemChange={(id, item) =>
            self.send(ChangeShoppingItem(id, item))
          }
        />
        <button
          onClick={_event => self.send(AddShoppingItem)}
          disabled={self.state.isLoading}>
          {ReasonReact.string("Add shopping item")}
        </button>
      </>,
  };
};
