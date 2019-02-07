open Json.Decode;
open Types;
open Utils;

let decodeAssignee = (json): assignee => {
  {name: json |> field("name", string), id: json |> field("id", int)};
};

let decodeShoppingItem = (json): shoppingItem => {
  {
    product: json |> field("product", string),
    note: json |> optional(field("note", string)) |> defaultIfNone(""),
    assignee: json |> optional(field("assignee", decodeAssignee)),
  };
};

let decodeShoppingList = (json): shoppingList => {
  {
    name: json |> field("name", string),
    status: json |> field("status", string),
    items: json |> field("items", array(decodeShoppingItem)),
  };
};
