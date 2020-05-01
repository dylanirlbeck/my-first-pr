let str = React.string;
let logo: string = [%raw "require('../assets/logo.png')"];

[@react.component]
let make = (~username) => {
  open Js.Promise;
  let (data, setData) = React.useState(_ => None);

  React.useEffect1(
    () => {
      Js.log(username);
      setData(_ => None);
      Api.sendQuery(~query=Api.makeQuery(username))
      |> then_(res => {
           setData(_ => Some(res));
           resolve();
         })
      |> catch(_ => {
           setData(_ => None);
           resolve();
         })
      |> ignore;
      None;
    },
    [|username|],
  );

  // TODO add a Loading spinner
  switch (data) {
  | None => <div> "Loading..."->React.string </div>
  | Some(d) =>
    Js.log(d);
    <div className=[%tw "h-screen justify-center flex items-center"]>
      <div className=[%tw "max-w-sm rounded overflow-hidden shadow-lg p-4"]>
        <img className=[%tw "w-full"] src=logo alt="Sunset in the mountains" />
        <div className=[%tw "px-6 py-4"]>
          <div className=[%tw "font-bold text-xl"]>
            {"RE-Tailwind" |> str}
          </div>
          <p className=[%tw "text-gray-700 text-base"]>
            {"A reason react starter with tailwind" |> str}
          </p>
        </div>
        <div className=[%tw "px-6 py-4"]>
          {[|"Reason React", "Tailwind"|]
           |> Array.map(tag =>
                <span
                  key=tag
                  className=[%tw
                    "inline-block bg-gray-200 rounded-full px-3 py-1 text-sm font-semibold text-gray-700 mr-2 mt-2"
                  ]>
                  {"#" ++ tag |> str}
                </span>
              )
           |> React.array}
        </div>
      </div>
    </div>;
  };
};
