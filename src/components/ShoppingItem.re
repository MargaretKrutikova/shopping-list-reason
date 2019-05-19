open Types;
open Dropdown;

module Styles = {
  open Css;

  let gridItem =
    style([display(`flex), alignItems(`center), justifyContent(`center)]);

  let assigneeBtnSize = 35;

  let assigneeBtn =
    style([
      width(px(assigneeBtnSize)),
      height(px(assigneeBtnSize)),
      borderRadius(pct(50.0)),
      outlineStyle(`none),
      fontSize(px(16)),
    ]);
};

let getAssigneeLetter = (assignee: string) => String.sub(assignee, 0, 1);

[@react.component]
let make =
    (
      ~item: shoppingItem,
      ~onItemChange,
      ~id: int,
      ~assignees: array(assignee),
    ) => {
  let handleProductChange = event => {
    let newItem = {...item, product: ReactEvent.Form.target(event)##value};
    onItemChange(id, newItem);
  };
  let handleNoteChange = event => {
    let newItem = {...item, note: ReactEvent.Form.target(event)##value};
    onItemChange(id, newItem);
  };
  // TODO: test, remove later
  let (assignee, setAssignee) = React.useState(() => "");
  let selectOption = o => setAssignee(_ => o);

  let assigneeOptions = assignees->Belt.Array.map(assignee => assignee.name);

  <Grid type_={Container(`nowrap)}>
    <Grid type_={Item(Grow)}>
      <TextField
        placeholder="Product"
        value={item.product}
        onChange=handleProductChange
        disableGutter=true
      />
    </Grid>
    <Grid type_={Item(Grow)}>
      <TextField
        placeholder="Note"
        value={item.note}
        onChange=handleNoteChange
        disableGutter=true
      />
    </Grid>
    <Grid type_={Item(Auto)} className=Styles.gridItem>
      <Dropdown
        selected=assignee
        options=assigneeOptions
        align=Right
        selectOption
        renderDropdownButton={toggle =>
          <button onClick=toggle className=Styles.assigneeBtn>
            {switch (assignee) {
             | "" => ReasonReact.string("+")
             | value =>
               value
               |> getAssigneeLetter
               |> String.uppercase
               |> ReasonReact.string
             }}
          </button>
        }
      />
    </Grid>
  </Grid>;
};
