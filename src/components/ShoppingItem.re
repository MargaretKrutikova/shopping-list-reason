open Types;

let component = ReasonReact.statelessComponent("ShoppingItem");

let make = (~item: shoppingItem, ~onItemChange, ~id: int, _children) => {
  let handleProductChange = event => {
    let newItem = {...item, product: ReactEvent.Form.target(event)##value};
    onItemChange(id, newItem);
  };
  let handleNoteChange = event => {
    let newItem = {...item, note: ReactEvent.Form.target(event)##value};
    onItemChange(id, newItem);
  };
  {
    ...component,
    render: _self =>
      <Grid type_=Container key={string_of_int(id)}>
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
