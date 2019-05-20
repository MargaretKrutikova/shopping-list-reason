open ClickOutside;

let str = ReasonReact.string;

type alignType =
  | Left
  | Right
  | Center;

module Styles = {
  open Css;

  let triangleWidthPx = 9;
  let alignShiftPx = Theme.spacingPx.small;
  let optionsTopPx = 12;

  let getOptionsContainerAlign = (align: alignType) =>
    switch (align) {
    | Center => `center
    | Left => `flexStart
    | Right => `flexEnd
    };

  let getOptionsAlign = (align: alignType) =>
    switch (align) {
    | Center => []
    | Left => [left(px(- alignShiftPx))]
    | Right => [right(px(- alignShiftPx))]
    };

  let dropdown = style([position(relative), userSelect(`none)]);
  let dropdownButton =
    style([border(px(1), solid, `rgba((0, 0, 0, 0.4))), padding(px(4))]);

  let optionsContainer = style([position(relative), width(pct(100.0))]);

  let options = (align: alignType) =>
    merge([
      style([
        position(absolute),
        top(px(0)),
        minWidth(px(100)),
        padding2(~h=px(0), ~v=px(Theme.spacingPx.xsmall)),
        border(px(1), solid, `rgba((200, 200, 200, 1.0))),
        boxSizing(borderBox),
        background(white),
        marginTop(px(optionsTopPx)),
        borderRadius(px(4)),
        boxShadow(
          ~x=px(0),
          ~y=px(3),
          ~blur=px(12),
          `rgba((27, 31, 25, 0.15)),
        ),
        zIndex(1),
      ]),
      style(getOptionsAlign(align)),
    ]);

  let triangle =
    merge([
      style([
        width(pct(100.0)),
        position(absolute),
        top(px(0)),
        boxSizing(borderBox),
        marginTop(px(optionsTopPx + 1)),
        zIndex(2),
        before([
          position(absolute),
          left(pct(50.0)),
          transform(`translate((pct(-50.0), px(0)))),
          top(px(- triangleWidthPx * 2)),
          display(`inlineBlock),
          contentRule(""),
          border(px(triangleWidthPx), solid, `transparent),
          borderBottomColor(`rgba((200, 200, 200, 1.0))),
        ]),
        after([
          position(absolute),
          top(px(- (triangleWidthPx * 2 - 2))),
          left(`calc((`add, pct(50.0), px(0)))),
          transform(`translate((pct(-50.0), px(0)))),
          display(`inlineBlock),
          contentRule(""),
          border(px(triangleWidthPx - 1), solid, `transparent),
          borderBottomColor(white),
        ]),
      ]),
    ]);

  let optionItem = isSelected =>
    style([
      padding2(~h=px(Theme.spacingPx.small), ~v=px(Theme.spacingPx.xsmall)),
      boxSizing(borderBox),
      backgroundColor(isSelected ? `rgba((0, 0, 0, 0.4)) : transparent),
      hover([
        background(
          isSelected ? `rgba((0, 0, 0, 0.4)) : `rgba((0, 0, 0, 0.1)),
        ),
      ]),
    ]);
};

type state = {isOpen: bool};

type action =
  | Open
  | Close
  | Toggle;

let reducer = (state, action) => {
  switch (action) {
  | Open => {isOpen: true}
  | Close => {isOpen: false}
  | Toggle => {isOpen: !state.isOpen}
  };
};

[@react.component]
let make =
    (
      ~selected: option(string),
      ~options: array(string),
      ~selectOption: string => unit,
      ~renderDropdownButton=?,
      ~align=Center,
    ) => {
  let (state, dispatch) = React.useReducer(reducer, {isOpen: false});
  let selectAndClose = (item: string) => {
    selectOption(item);
    dispatch(Close);
  };

  let dropdownRef = useClickOutside(_ => dispatch(Close));
  let toggleOpen = _ => dispatch(Toggle);

  <div className=Styles.dropdown ref={ReactDOMRe.Ref.domRef(dropdownRef)}>
    {switch (renderDropdownButton) {
     | Some(render) => render(toggleOpen)
     | None =>
       <div onClick=toggleOpen className=Styles.dropdownButton>
         {switch (selected) {
          | Some(value) => str(value)
          | None => str("")
          }}
       </div>
     }}
    {state.isOpen
       ? <div className=Styles.optionsContainer>
           <div className=Styles.triangle />
           <div className={Styles.options(align)}>
             {options->Belt.Array.mapWithIndex((index, item) =>
                <div
                  key={string_of_int(index)}
                  onClick={_ => selectAndClose(item)}
                  className={Styles.optionItem(
                    selected->Belt.Option.mapWithDefault(false, val_ =>
                      val_ === item
                    ),
                  )}>
                  {item |> str}
                </div>
              )
              |> ReasonReact.array}
           </div>
         </div>
       : ReasonReact.null}
  </div>;
};
