open Css;

type flexBasisLength = [
  length
  | `auto
  | `fill
  | `content
  | `maxContent
  | `minContent
  | `fitContent
];

type gridItemWidth =
  | Columns(int)
  | Grow
  | Auto
  | Flex(float, int, flexBasisLength);

type containerWrap = [ | `nowrap | `wrap | `wrapReverse];

type gridType =
  | Container(containerWrap)
  | Item(gridItemWidth);

module Styles = {
  let containerSpacing = (spacing: int) => [
    width(`calc((`add, pct(100.0), px(spacing)))),
    margin(px(- spacing / 2)),
  ];
  let itemSpacing = (spacing: int) => [padding(px(spacing / 2))];

  let calculateColumnsWidth = (columns: int) =>
    float_of_int(columns) /. 12.0 *. 100.0;

  let getFlexStyles = (grow, shrink, basis) => [
    flexGrow(grow),
    flexShrink(shrink),
    flexBasis(basis),
  ];

  let gridItemWidthStyle = (width: gridItemWidth) =>
    switch (width) {
    | Columns(columns) =>
      let widthPct = calculateColumnsWidth(columns);

      getFlexStyles(0.0, 1, pct(widthPct)) @ [maxWidth(pct(widthPct))];
    | Flex(grow, shrink, basis) => getFlexStyles(grow, shrink, basis)
    | Grow => getFlexStyles(1.0, 1, auto)
    | Auto => []
    };

  let gridContainer = (wrapValue: containerWrap) =>
    style(
      [display(`flex), flexWrap(wrapValue), boxSizing(borderBox)]
      @ containerSpacing(Theme.spacingPx.small)
      @ [
        media(Breakpoints.up(Md), containerSpacing(Theme.spacingPx.medium)),
      ],
    );

  let gridItem = (itemWidth: gridItemWidth) =>
    style(
      [boxSizing(borderBox)]
      @ gridItemWidthStyle(itemWidth)
      @ itemSpacing(Theme.spacingPx.small)
      @ [media(Breakpoints.up(Md), itemSpacing(Theme.spacingPx.medium))],
    );
};

let getGridStyles = (type_: gridType) => {
  switch (type_) {
  | Container(wrapValue) => Styles.gridContainer(wrapValue)
  | Item(width) => Styles.gridItem(width)
  };
};

[@react.component]
let make = (~type_: gridType, ~children, ~className=?) => {
  let gridClassName = getGridStyles(type_);
  let customClassName = Belt.Option.getWithDefault(className, "");

  <div className={j|$gridClassName $customClassName|j}> children </div>;
};
