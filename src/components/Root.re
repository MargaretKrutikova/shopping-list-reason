Css.insertRule("body { margin: 0 }");

let component = ReasonReact.statelessComponent("Root");

let make = _children => {
  ...component,
  render: _self => <PageContainer> <ShoppingList /> </PageContainer>,
};