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

let updateItems = (state: state, items: array(shoppingItem)) => {
  ...state,
  shoppingList: {
    ...state.shoppingList,
    items,
  },
};

let reducer = (state, action) => {
  switch (action) {
  | ShoppingListFetch => {...state, isLoading: true}
  | ShoppingListFetchSuccess(list) => {
      ...state,
      isLoading: false,
      shoppingList: list,
    }
  | ShoppingListFetchError => {
      ...state,
      isLoading: false,
      error: Some("Failed to fetch shopping list"),
    }
  | AddShoppingItem =>
    let newItem: shoppingItem = {product: "", note: "", assignee: None};
    let items = Array.append(state.shoppingList.items, [|newItem|]);
    updateItems(state, items);
  | ChangeShoppingItem(index, newItem) =>
    let updateFn = _item => newItem;
    let items = updateWithIndex(state.shoppingList.items, updateFn, index);
    updateItems(state, items);
  };
};

let initialState = () => {
  isLoading: false,
  error: None,
  shoppingList: {
    name: "",
    status: "",
    items: [||],
  },
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState());
  React.useEffect0(() => {
    dispatch(ShoppingListFetch);
    Js.Promise.(
      getShoppingList()
      |> then_(result =>
           switch (result) {
           | Belt.Result.Ok(list) =>
             dispatch(ShoppingListFetchSuccess(list)) |> resolve
           | Belt.Result.Error () =>
             dispatch(ShoppingListFetchError) |> resolve
           }
         )
    )
    |> ignore;
    None;
  });

  <>
    <h1> {ReasonReact.string("Shopping List")} </h1>
    {state.isLoading
       ? <span> {ReasonReact.string("...Loading")} </span> : ReasonReact.null}
    <ShoppingList
      list={state.shoppingList}
      onItemChange={(id, item) => dispatch(ChangeShoppingItem(id, item))}
    />
    <button
      onClick={_event => dispatch(AddShoppingItem)}
      disabled={state.isLoading}>
      {ReasonReact.string("Add shopping item")}
    </button>
  </>;
};
