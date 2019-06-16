open Redux;

Css.insertRule("body { margin: 0 }");

[@react.component]
let make = () => {
  <App.Store.Provider value=App.Store.appStore>
    <PageContainer> <ShoppingListPage /> </PageContainer>
  </App.Store.Provider>;
};
