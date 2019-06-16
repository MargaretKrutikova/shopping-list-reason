module Store = {
  type t('action, 'state) = {
    mutable state: 'state,
    mutable reducer: ('state, 'action) => 'state,
    mutable listeners: list(unit => unit),
    customDispatcher:
      option((t('action, 'state), 'action => unit, 'action) => unit),
  };
  let create = (~reducer, ~preloadedState, ~enhancer=?, ()) =>
    switch (preloadedState, enhancer, reducer) {
    | (preloadedState, None, reducer) => {
        state: preloadedState,
        listeners: [],
        reducer,
        customDispatcher: None,
      }
    | (preloadedState, Some(enhancer), reducer) => {
        state: preloadedState,
        listeners: [],
        reducer,
        customDispatcher: Some(enhancer),
      }
    };
  let unsubscribe = (store, listener, ()) =>
    store.listeners = List.filter(l => listener !== l, store.listeners);
  let subscribe = (store, listener) => {
    store.listeners = [listener, ...store.listeners];
    unsubscribe(store, listener);
  };
  let nativeDispatch = (store, action) => {
    store.state = store.reducer(store.state, action);
    List.iter(listener => listener(), store.listeners);
  };
  let dispatch = (store, action) =>
    switch (store.customDispatcher) {
    | Some(customDispatcher) =>
      customDispatcher(store, nativeDispatch(store), action)
    | None => nativeDispatch(store, action)
    };
  let getState = store => store.state;
  let replaceReducer = (store, reducer) => store.reducer = reducer;
};
