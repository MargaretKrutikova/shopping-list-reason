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
      [display(`flex), flexWrap(`wrap), boxSizing(`borderBox)]
      @ containerSpacing(Theme.spacingPx.small)
      @ [
        media(Breakpoints.up(Md), containerSpacing(Theme.spacingPx.medium)),
      ],
    );

  let gridItem = (columns: int) => {
    let widthPct =
      float_of_int(columns)
      /. 12.0
      *. float_of_int(Js.Math.pow_int(10, 7))
      /. float_of_int(Js.Math.pow_int(10, 5));
    style(
      [
        flexGrow(0.0),
        flexShrink(1),
        flexBasis(pct(widthPct)),
        maxWidth(pct(widthPct)),
        boxSizing(`borderBox),
      ]
      @ itemSpacing(Theme.spacingPx.small)
      @ [media(Breakpoints.up(Md), itemSpacing(Theme.spacingPx.medium))],
    );
  };
};

type gridType =
  | Container
  | Item(int);

let getGridStyles = (type_: gridType) => {
  switch (type_) {
  | Container => Styles.gridContainer
  | Item(width) => Styles.gridItem(width)
  };
};

let component = ReasonReact.statelessComponent("Grid");

[@react.component]
let make = (~type_: gridType, ~children, ~className=?) => {
  let gridClassName = getGridStyles(type_);
  let customClassName = Belt.Option.getWithDefault(className, "");

  <div className={j|$gridClassName $customClassName|j}> children </div>;
};
