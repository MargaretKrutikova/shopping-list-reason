open Store;

module type Config = {
  type context;
  let defaultValue: context;
};

module ReduxContext = {
  type state = {count: int};
  type action =
    | Increment
    | Decrement
    | NoChange;

  let reducer = state =>
    fun
    | Increment => {count: state.count + 1}
    | Decrement => {count: state.count - 1}
    | NoChange => state;

  type store = Store.t(action, state);

  let appStore = Store.create(~reducer, ~preloadedState={count: 0}, ());

  let context = React.createContext(appStore);

  module Provider = {
    let make = context->React.Context.provider;

    [@bs.obj]
    external makeProps:
      (~value: store, ~children: React.element, ~key: string=?, unit) =>
      {
        .
        "value": store,
        "children": React.element,
      } =
      "";
  };
};

let useSelector = selector => {
  let store = React.useContext(ReduxContext.context);

  let (syncedState, setSyncedState) =
    React.useState(() => selector(Store.getState(store)));

  React.useEffect1(
    () => {
      let unsubscribe =
        Store.subscribe(store, () =>
          setSyncedState(_ => selector(Store.getState(store)))
        );

      Some(unsubscribe);
    },
    [|store|],
  );

  syncedState;
};

let useDispatch = () => {
  let store = React.useContext(ReduxContext.context);

  Store.dispatch(store);
};
