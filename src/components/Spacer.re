let space = inner => inner ? "p" : "m";
let create = (inner, dir, unit) =>
  unit != 0 ? space(inner) ++ dir ++ "-" ++ string_of_int(unit) : "";

[@genType "Spacer"]
[@react.component]
let make =
    (
      ~children=?,
      ~inner=false,
      ~top=0,
      ~bottom=0,
      ~left=0,
      ~right=0,
      ~all=0,
      ~x=0,
      ~y=0,
    ) => {
  let createSpacer = create(inner);

  let className =
    Cn.make([
      createSpacer("t", top),
      createSpacer("b", bottom),
      createSpacer("l", left),
      createSpacer("r", right),
      createSpacer("y", y),
      createSpacer("x", x),
      createSpacer("", all),
    ]);

  <div className>
    {switch (children) {
     | None => React.null
     | Some(c) => c
     }}
  </div>;
};
