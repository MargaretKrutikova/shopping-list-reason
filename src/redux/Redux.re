open Store;

module type Config = {
  type state;
  type action;
  let defaultValue: Store.t(action, state);
};

module ReduxContext = (Config: Config) => {
  let context = React.createContext(Config.defaultValue);

  module Provider = {
    let make = context->React.Context.provider;

    [@bs.obj]
    external makeProps:
      (
        ~value: Store.t('a, 's),
        ~children: React.element,
        ~key: string=?,
        unit
      ) =>
      {
        .
        "value": Store.t('a, 's),
        "children": React.element,
      } =
      "";
  };

  let useSelector = selector => {
    let store = React.useContext(context);

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
    let store = React.useContext(context);

    Store.dispatch(store);
  };
};
