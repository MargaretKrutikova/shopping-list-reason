open Types;

[@react.component]
let make =
    (
      ~list: shoppingList,
      ~onItemChange: (int, shoppingItem) => unit,
      ~assignees: array(assignee),
    ) => {
  <div
    className=Css.(
      style([
        media(Breakpoints.up(Md), [width(pct(70.0))]),
        media(Breakpoints.up(Lg), [width(pct(50.0))]),
      ])
    )>
    {list.items
     |> Array.mapi((index, item) =>
          <ShoppingItem
            key={string_of_int(index)}
            item
            id=index
            onItemChange
            assignees
          />
        )
     |> ReasonReact.array}
  </div>;
};
