[@react.component]
let make = () => {
  let (username, setUsername) = Hooks.useInput("");
  let (actualUsername, setActualUsername) = React.useState(_ => None);

  <div
    className=[%tw
      "w-full h-full bg-white flex flex-col justify-start items-center"
    ]>
    <div>
      <h1 className=[%tw "text-6xl"]> "My First PR"->React.string </h1>
    </div>
    <div>
      <span>
        "View the details of your first pull request on GitHub"->React.string
      </span>
    </div>
    <div className=[%tw "flex flex-col items-center"]>
      <span className=[%tw "font-bold mb-2"]>
        "Enter in your GitHub username:"->React.string
      </span>
      <div className=[%tw "flex"]>
        <span
          className=[%tw
            "text-sm border border-2 rounded-l px-4 py-2
              bg-gray-300 whitespace-no-wrap"
          ]>
          "@"->React.string
        </span>
        <input
          className=[%tw "border border-2 rounded-r w-full px-4 py-2"]
          type_="text"
          onChange=setUsername
          placeholder="dylanirlbeck"
        />
        <button
          className=[%tw
            "flex-shrink-0 bg-green-500 hover:bg-green-700
 border-green-500 hover:border-green-700 text-sm border-4 text-white py-1 px-2
 rounded"
          ]
          onClick={_ => {setActualUsername(_ => Some(username))}}
          type_="button">
          "Submit"->React.string
        </button>
      </div>
    </div>
    <Card username=actualUsername />
  </div>;
};
