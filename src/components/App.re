open Store;
open Redux;

module Store = {
  type appState = {count: int};
  type appAction =
    | Increment
    | Decrement
    | NoChange;

  let reducer = state =>
    fun
    | Increment => {count: state.count + 1}
    | Decrement => {count: state.count - 1}
    | NoChange => state;

  let appStore = Store.create(~reducer, ~preloadedState={count: 0}, ());

  include ReduxContext({
    type state = appState;
    type action = appAction;
    let defaultValue = appStore;
  });
};
