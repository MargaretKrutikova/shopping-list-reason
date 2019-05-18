open Json.Decode;
open Types;
open Utils;

let decodeShoppingItem = (json): shoppingItem => {
  {
    product: json |> field("product", string),
    note: json |> optional(field("note", string)) |> defaultIfNone(""),
    assignee: json |> optional(field("assignee", string)),
    isPurchased: json |> field("isPurchased", bool),
  };
};

let decodeListStatus = (jsonString): listStatus => {
  switch (jsonString |> Js.String.toLowerCase) {
  | "editing" => Editing
  | "shopping" => Shopping
  | "completed" => Completed
  | _ =>
    raise(DecodeError("Status '" ++ jsonString ++ "' is not supported!"))
  };
};

let decodeShoppingList = (json): shoppingList => {
  {
    name: json |> field("name", string),
    status: json |> field("status", string) |> decodeListStatus,
    items: json |> field("items", array(decodeShoppingItem)),
  };
};
