[@react.component]
let make = (~children) => {
  <div
    className=Css.(
      style([
        padding2(~v=zero, ~h=px(Theme.spacingPx.large)),
        backgroundColor(Theme.colors.bgColor),
        overflow(auto),
        minHeight(vh(100.)),
        media(
          Breakpoints.down(Sm),
          [padding2(~v=zero, ~h=px(Theme.spacingPx.small))],
        ),
      ])
    )>
    <div
      className=Css.(
        style([
          maxWidth(px(Theme.pageMaxWidth)),
          margin2(~v=zero, ~h=auto),
        ])
      )>
      children
    </div>
  </div>;
};
