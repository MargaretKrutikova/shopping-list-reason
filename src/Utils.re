let updateWithIndex = (array: array('a), updateFn: 'a => 'a, index: int) =>
  array->Belt.Array.mapWithIndex((i, value) =>
    i == index ? updateFn(value) : value
  );

let defaultIfNone = (defaultValue, optionValue) =>
  switch (optionValue) {
  | Some(value) => value
  | None => defaultValue
  };
