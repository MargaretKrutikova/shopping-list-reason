let component = ReasonReact.statelessComponent("Input");

let make = (~placeholder="", ~value, ~onChange, _children) => {
  ...component,
  render: _self =>
    <div
      className=Css.(
        style([
          marginBottom(px(Theme.spacingPx.xsmall)),
          media(
            Breakpoints.up(Md),
            [marginBottom(px(Theme.spacingPx.small))],
          ),
        ])
      )>
      <input
        type_="text"
        placeholder
        value
        onChange
        className=Css.(
          style([
            border(zero, none, transparent),
            outline(zero, `none, white),
            padding3(~top=px(10), ~h=px(7), ~bottom=px(6)),
            fontSize(px(18)),
            width(pct(100.)),
            color(Theme.colors.greyDefault),
            boxSizing(borderBox),
            borderRadius(px(0)),
            transitions([
              transition(
                ~duration=200,
                ~timingFunction=easeInOut,
                "border-bottom-color",
              ),
            ]),
            borderBottom(px(1), solid, `rgba((0, 0, 0, 0.42))),
            focus([
              borderBottomWidth(px(2)),
              borderBottomColor(`rgba((0, 0, 0, 0.8))),
              paddingBottom(px(5)),
            ]),
          ])
        )
      />
    </div>,
};
