open Redux;

Css.insertRule("body { margin: 0 }");

// create store and put it in context
// module StoreProvider = {
//   type state = {count: int};
//   type action =
//     | Increment
//     | Decrement
//     | NoChange;

//   let reducer = state =>
//     fun
//     | Increment => {count: state.count + 1}
//     | Decrement => {count: state.count - 1}
//     | NoChange => state;

//   type store = Store.t(action, state);

//   let appStore = Store.create(~reducer, ~preloadedState={count: 0}, ());

//   include ReduxContext({
//     type context = store;
//     let defaultValue = appStore;
//   });
// };

[@react.component]
let make = () => {
  <ReduxContext.Provider value=ReduxContext.appStore>
    <PageContainer> <ShoppingListPage /> </PageContainer>
  </ReduxContext.Provider>;
};
