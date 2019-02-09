let component = ReasonReact.statelessComponent("Input");

let make = (~placeholder="", ~value, ~onChange, _children) => {
  ...component,
  render: _self =>
    <div className=Css.(style([marginBottom(px(Theme.spacingPx.small))]))>
      <input
        type_="text"
        placeholder
        value
        onChange
        className=Css.(
          style([
            borderWidth(zero),
            borderBottom(px(1), solid, black),
            outline(zero, `none, white),
            padding2(~v=px(7), ~h=px(5)),
            fontSize(px(16)),
            width(pct(100.)),
            color(Theme.colors.greyDefault),
            boxSizing(borderBox),
            focus([borderBottom(px(2), solid, black)]),
          ])
        )
      />
    </div>,
};
