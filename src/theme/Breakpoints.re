type breakpoint =
  | Xs
  | Sm
  | Md
  | Lg
  | Xl;

let breakpointToPx = (bp: breakpoint) =>
  switch (bp) {
  | Xs => 0
  | Sm => 600
  | Md => 960
  | Lg => 1280
  | Xl => 1920
  };

let up = (bp: breakpoint) =>
  "(min-width: " ++ string_of_int(breakpointToPx(bp)) ++ "px)";
let down = (bp: breakpoint) =>
  "(max-width: " ++ string_of_int(breakpointToPx(bp)) ++ "px)";
