open Css;

module Styles = {
  open Css;

  let containerSpacing = (spacing: int) => [
    width(`calc((`add, pct(100.0), px(spacing)))),
    margin(px(- spacing / 2)),
  ];

  let itemSpacing = (spacing: int) => [padding(px(spacing / 2))];

  let gridContainer =
    style(
      [display(`flex)]
      @ containerSpacing(Theme.spacingPx.small)
      @ [
        media(Breakpoints.up(Md), containerSpacing(Theme.spacingPx.medium)),
      ],
    );

  let gridItem =
    style(
      [flexGrow(1.0), flexShrink(1), flexBasis(auto)]
      @ itemSpacing(Theme.spacingPx.small)
      @ [media(Breakpoints.up(Md), itemSpacing(Theme.spacingPx.medium))],
    );
};

type gridType =
  | Container
  | Item;

let getGridStyles = (type_: gridType) => {
  switch (type_) {
  | Container => Styles.gridContainer
  | Item => Styles.gridItem
  };
};

let component = ReasonReact.statelessComponent("Grid");

[@react.component]
let make = (~type_: gridType, ~children, ~className=?) => {
  let gridClassName = getGridStyles(type_);
  let customClassName = Belt.Option.getWithDefault(className, "");

  <div className={j|$gridClassName $customClassName|j}> children </div>;
};
