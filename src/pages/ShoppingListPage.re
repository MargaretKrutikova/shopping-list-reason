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
  | ApiCallError(string)
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
  | ApiCallError(errorMessage) => {
      ...state,
      isLoading: false,
      error: Some(errorMessage),
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

// TODO: Success/Failure actions instead of dispatch?
let fetchShoppingList = (dispatch: action => unit) =>
  Js.Promise.(
    getShoppingList()
    |> then_(result =>
         dispatch(ShoppingListFetchSuccess(result)) |> resolve
       )
    |> catch(_ =>
         dispatch(ApiCallError("Failed to fetch shopping list")) |> resolve
       )
  );

let startShopping = (items, dispatch: action => unit) => {
  dispatch(ShoppingListFetch);
  Js.Promise.(
    updateShoppingList(items)
    |> then_(_ => publishShoppingList())
    |> then_(_ => fetchShoppingList(dispatch))
    |> catch(_ =>
         dispatch(
           ApiCallError(
             "Network request failed - it's either update, fetch of publish :)",
           ),
         )
         |> resolve
       )
  )
  |> ignore;
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState());

  React.useEffect0(() => {
    dispatch(ShoppingListFetch);
    fetchShoppingList(dispatch) |> ignore;
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
    <button
      onClick={_ => startShopping(state.shoppingList.items, dispatch)}
      disabled={state.isLoading}>
      {ReasonReact.string("START")}
    </button>
  </>;
};
