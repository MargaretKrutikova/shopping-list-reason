open Types;

let component = ReasonReact.statelessComponent("ShoppingItem");

let make = (~item: shoppingItem, ~onProductChange, ~onNoteChange, _children) => {
  let handleProductChange = event =>
    onProductChange(ReactEvent.Form.target(event)##value);
  let handleNoteChange = event =>
    onNoteChange(ReactEvent.Form.target(event)##value);
  {
    ...component,
    render: _self =>
      <Grid type_=Container>
        <Grid type_=Item>
          <TextField
            placeholder="Product"
            value={item.product}
            onChange=handleProductChange
          />
        </Grid>
        <Grid type_=Item>
          <TextField
            placeholder="Note"
            value={item.note}
            onChange=handleNoteChange
          />
        </Grid>
      </Grid>,
  };
};