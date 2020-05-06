let str = React.string;
let logo: string = [%raw "require('../assets/logo.png')"];
let prImage: string = [%raw "require('../assets/pull_request.png')"];

let fakeData: Decoder.pullRequest = {
  repoName: "groot-groups-store",
  avatarUrl: "https://avatars3.githubusercontent.com/u/35497479?u=67e4d7cdce1cd6519f608c43e962e0d94582b22b&v=4",
  body: "",
  state: "MERGED",
  title: "Fixed ICPC meetingTime, meetingDay, chairs, and email",
  url: "https://github.com/acm-uiuc/groot-groups-store/pull/65",
  date: "2019-01-26T23:53:54Z",
};

type queryState =
  | Empty
  | Loading
  | Error
  | Data(Js.Json.t);

exception PrStateException(string);

module Title = {
  [@react.component]
  let make = (~text) => {
    <div className=[%tw "px-4 py-8"]>
      <span className=[%tw "text-2xl font-bold text-gray-800"]>
        text->React.string
      </span>
    </div>;
  };
};

module Body = {
  [@react.component]
  let make = (~prTitle, ~prDescription) => {
    <div className=[%tw "px-4 py-8 rounded-b-md"]>
      <span
        className=[%tw "block text-lg text-gray-800 font-bold tracking-wide"]>
        {prTitle |> str}
      </span>
      <p className=[%tw "block text-gray-600 text-sm"]>
        {prDescription |> str}
      </p>
    </div>;
  };
};

module State = {
  [@react.component]
  let make = (~state) => {
    let (background, name) =
      switch (state) {
      | "OPEN" => ("bg-green-400", "open")
      | "CLOSED" => ("bg-red-400", "closed")
      | "MERGED" => ("bg-purple-400", "merged")
      | _ => raise(PrStateException(state))
      };
    <span
      className={Cn.make([
        "inline-block rounded-full px-3 py-1 text-lg font-semibold
      text-white mr-2",
        background,
      ])}>
      name->React.string
    </span>;
  };
};

module Date = {
  [@react.component]
  let make = (~date) => {
    <span className="text-lg font-light text-gray-600">
      date->React.string
    </span>;
  };
};

[@react.component]
let make = (~username) => {
  open Js.Promise;

  let (data, setData) = React.useState(_ => Empty);

  React.useEffect1(
    () => {
      if (Belt.Option.getWithDefault(username, "") != "") {
        Js.log(username);
        setData(_ => Loading);
        Api.sendQuery(~query=Api.makeQuery(username))
        |> then_(res => {
             setData(_ => Data(res));
             resolve();
           })
        |> catch(_ => {
             setData(_ => Error);
             resolve();
           })
        |> ignore;
      };
      None;
    },
    [|username|],
  );

  // TODO add a Loading spinner
  <div className=[%tw "flex-grow flex flex-col justify-center"]>
    {switch (data) {
     | Empty =>
       let pr = fakeData;
       <div
         className=[%tw
           "max-w-sm hover:bg-gray-100 rounded overflow-hidden shadow-lg
               p-4 cursor-pointer"
         ]
         onClick={_ => {
           let window = Webapi.Dom.window;
           window
           ->(Webapi.Dom.Window.open_(~url=pr.url, ~name="repoWindow"))
           ->ignore;
         }}>
         <Title text={pr.repoName} />
         <Body prTitle={pr.title} prDescription={pr.body} />
         <div className=[%tw "flex items-center justify-between"]>
           <State state={pr.state} />
           <Date date={Js.Date.toDateString(Js.Date.fromString(pr.date))} />
         </div>
       </div>;
     | Error => <div> "Error..."->React.string </div>
     | Loading => <div> "Loading..."->React.string </div>
     | Data(d) =>
       let pr = Api.decode(d);
       Js.log(pr);
       <div
         className=[%tw
           "max-w-sm hover:bg-gray-100 rounded overflow-hidden shadow-lg
               p-4 cursor-pointer"
         ]
         onClick={_ => {
           let window = Webapi.Dom.window;
           window
           ->(Webapi.Dom.Window.open_(~url=pr.url, ~name="repoWindow"))
           ->ignore;
         }}>
         <Title text={pr.repoName} />
         <Body prTitle={pr.title} prDescription={pr.body} />
         <div className=[%tw "flex items-center justify-between"]>
           <State state={pr.state} />
           <Date
             date={Js.Date.toLocaleDateString(Js.Date.fromString(pr.date))}
           />
         </div>
       </div>;
     }}
  </div>;
};
