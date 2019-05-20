open Types;

[@react.component]
let make = (~list: shoppingList, ~onItemToggle: int => unit) => {
  <div
    className=Css.(
      style([
        media(Breakpoints.up(Md), [width(pct(70.0))]),
        media(Breakpoints.up(Lg), [width(pct(50.0))]),
      ])
    )>
    {list.items
     |> Array.mapi((index, item) =>
          <Grid type_={Container(`nowrap)} key={string_of_int(index)}>
            <Grid type_={Item(Grow)}>
              <span> {ReasonReact.string(item.product)} </span>
            </Grid>
            <Grid type_={Item(Grow)}>
              <span> {ReasonReact.string(item.note)} </span>
            </Grid>
            <Grid type_={Item(Auto)}>
              <input
                type_="checkbox"
                checked={item.isPurchased}
                onChange={_ => onItemToggle(index)}
              />
            </Grid>
          </Grid>
        )
     |> ReasonReact.array}
  </div>;
};
