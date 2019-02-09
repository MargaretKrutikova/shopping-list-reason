open Css;

let gridContainer = (spacing: int) => [
  width(`calc((`add, pct(100.0), px(spacing)))),
  margin(px(- spacing / 2)),
];

let gridItem = (spacing: int) => [padding(px(spacing / 2))];

let component = ReasonReact.statelessComponent("Grid");

type gridType =
  | Container
  | Item;

let make = (~type_: gridType, children) => {
  let getGridStyles = (): list(rule) => {
    switch (type_) {
    | Container =>
      [display(`flex)]
      @ gridContainer(Theme.spacingPx.small)
      @ [media(Breakpoints.up(Md), gridContainer(Theme.spacingPx.medium))]

    | Item =>
      [flexGrow(1.0), flexShrink(1), flexBasis(auto)]
      @ gridItem(Theme.spacingPx.small)
      @ [media(Breakpoints.up(Md), gridItem(Theme.spacingPx.medium))]
    };
  };
  {
    ...component,
    render: _self =>
      <div className={Css.style(getGridStyles())}> ...children </div>,
  };
};
