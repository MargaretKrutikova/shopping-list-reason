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
  | ApiCallStarted
  | ShoppingListFetchSuccess(shoppingList)
  | ApiCallError(string)
  | AddShoppingItem
  | ChangeShoppingItem(int, shoppingItem)
  | SetListStatus(listStatus)
  | ToggleShoppingItemPurchased(int);

let updateItems = (state: state, items: array(shoppingItem)) => {
  ...state,
  shoppingList: {
    ...state.shoppingList,
    items,
  },
};

let reducer = (state, action) => {
  switch (action) {
  | ApiCallStarted => {...state, isLoading: true}
  | ShoppingListFetchSuccess(list) => {
      ...state,
      isLoading: false,
      shoppingList: list,
    }
  | ApiCallError(errorMessage) =>
    Js.log(errorMessage);
    {...state, isLoading: false, error: Some(errorMessage)};
  | AddShoppingItem =>
    let newItem: shoppingItem = {
      product: "",
      note: "",
      assignee: None,
      isPurchased: false,
    };
    let items = Array.append(state.shoppingList.items, [|newItem|]);
    updateItems(state, items);
  | ChangeShoppingItem(index, newItem) =>
    if (state.shoppingList.status != Editing) {
      state;
    } else {
      let updateFn = _item => newItem;
      let items = updateWithIndex(state.shoppingList.items, updateFn, index);
      updateItems(state, items);
    }
  | ToggleShoppingItemPurchased(index) =>
    if (state.shoppingList.status != Shopping) {
      state;
    } else {
      let updateFn = item => {...item, isPurchased: !item.isPurchased};
      let items = updateWithIndex(state.shoppingList.items, updateFn, index);
      updateItems(state, items);
    }
  | SetListStatus(status) => {
      ...state,
      shoppingList: {
        ...state.shoppingList,
        status,
      },
    }
  };
};

let initialState = () => {
  isLoading: false,
  error: None,
  shoppingList: {
    name: "",
    status: Editing,
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
    |> catch(e => {
         Js.log(e);
         dispatch(ApiCallError("Failed to fetch shopping list")) |> resolve;
       })
  );

let startShopping = (items, dispatch: action => unit) => {
  dispatch(ApiCallStarted);
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
    // TODO: Remove when the API is in place?
    |> then_(_ => dispatch(SetListStatus(Shopping)) |> resolve)
  )
  |> ignore;
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState());

  React.useEffect0(() => {
    dispatch(ApiCallStarted);
    fetchShoppingList(dispatch) |> ignore;
    None;
  });

  <>
    <h1> {ReasonReact.string("Shopping List")} </h1>
    {state.isLoading
       ? <span> {ReasonReact.string("...Loading")} </span> : ReasonReact.null}
    {switch (state.shoppingList.status) {
     | Shopping =>
       <>
         <LiveShoppingList
           // TODO: disabled={!state.isLoading}
           list={state.shoppingList}
           onItemToggle={id => dispatch(ToggleShoppingItemPurchased(id))}
         />
         <button onClick={_ => dispatch(SetListStatus(Editing))}>
           // TODO: Change status on the server?
            {ReasonReact.string("Edit")} </button>
         <button> {ReasonReact.string("Complete")} </button>
       </>
     | Editing =>
       <>
         <ShoppingList
           // TODO: disabled={!state.isLoading}
           list={state.shoppingList}
           onItemChange={(id, item) =>
             dispatch(ChangeShoppingItem(id, item))
           }
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
       </>
     | Completed =>
       <div> {ReasonReact.string("[COMPLETED PLACEHOLDER]")} </div>
     }}
  </>;
};
