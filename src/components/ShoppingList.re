open Types;

let component = ReasonReact.statelessComponent("ShoppingList");

let make = (~list: shoppingList, ~onItemChange, _children) => {
  ...component,
  render: _self =>
    <>
      <div
        className=Css.(
          style([
            media(Breakpoints.up(Md), [width(pct(60.0))]),
            media(Breakpoints.up(Lg), [width(pct(40.0))]),
          ])
        )>
        {list.items
         |> Array.mapi((index, item) =>
              <ShoppingItem item id=index onItemChange />
            )
         |> ReasonReact.array}
      </div>
    </>,
};
