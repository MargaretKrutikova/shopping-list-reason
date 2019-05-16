open ClickOutside;

let str = ReasonReact.string;

module Styles = {
  open Css;

  let dropdown = style([minWidth(px(100)), userSelect(`none)]);
  let dropdownButton =
    style([border(px(1), solid, `rgba((0, 0, 0, 0.4))), padding(px(4))]);

  let optionsContainer =
    style([position(relative), display(`flex), justifyContent(`center)]);
  let options =
    style([
      position(absolute),
      top(px(0)),
      padding2(~h=px(0), ~v=px(4)),
      border(px(1), solid, `rgba((0, 0, 0, 0.4))),
      width(pct(120.0)),
      boxSizing(borderBox),
      background(white),
      marginTop(px(Theme.spacingPx.small)),
      borderRadius(px(3)),
      before([
        position(absolute),
        top(px(-16)),
        left(`calc((`sub, pct(50.0), px(8)))),
        display(`inlineBlock),
        contentRule(""),
        border(px(8), solid, `transparent),
        borderBottomColor(`rgba((200, 200, 200, 1.0))),
      ]),
      after([
        position(absolute),
        top(px(-14)),
        left(`calc((`sub, pct(50.0), px(7)))),
        display(`inlineBlock),
        contentRule(""),
        border(px(7), solid, `transparent),
        borderBottomColor(`rgba((255, 255, 255, 1.0))),
      ]),
    ]);

  let optionItem = isSelected =>
    style([
      padding2(~h=px(8), ~v=px(4)),
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
    (~selected="", ~options: array(string), ~selectOption: string => unit) => {
  let (state, dispatch) = React.useReducer(reducer, {isOpen: false});
  let select = (item: string) => {
    selectOption(item);
    dispatch(Close);
  };

  let dropdownRef = useClickOutside(_ => dispatch(Close));

  <div className=Styles.dropdown ref={ReactDOMRe.Ref.domRef(dropdownRef)}>
    <div onClick={_ => dispatch(Toggle)} className=Styles.dropdownButton>
      {ReasonReact.string(selected != "" ? selected : "Select value")}
    </div>
    {state.isOpen
       ? <div className=Styles.optionsContainer>
           <div className=Styles.options>
             {options->Belt.Array.mapWithIndex((index, item) =>
                <div
                  key={string_of_int(index)}
                  onClick={_ => select(item)}
                  className={Styles.optionItem(item == selected)}>
                  {item |> ReasonReact.string}
                </div>
              )
              |> ReasonReact.array}
           </div>
         </div>
       : ReasonReact.null}
  </div>;
};
