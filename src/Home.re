let githubIcon: string = [%raw "require('/assets/github.png')"];

module Header = {
  [@react.component]
  let make = () => {
    <div
      className=[%tw
        "flex flex-row items-center w-full bg-gray-300 justify-center py-4"
      ]>
      <img className=[%tw "flex"] src=githubIcon />
      <Spacer left=8 />
      <div className=[%tw "flex flex-col items-center"]>
        <h3 className=[%tw "flex text-6xl font-semibold"]>
          "My First PR"->React.string
        </h3>
        <Spacer left=4 />
        <span className=[%tw "flex"]>
          "Revisit your very first GitHub pull request!"->React.string
        </span>
      </div>
    </div>;
  };
};

module Input = {
  [@react.component]
  let make = (~setActualUsername) => {
    let (username, setUsername) = Hooks.useInput("");

    <div className=[%tw "flex flex-col items-center"]>
      <span className=[%tw "font-bold text-xl mb-2"]>
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
          className=[%tw "border border-2 rounded-r w-full px-8 py-2"]
          type_="text"
          onChange=setUsername
          placeholder="dylanirlbeck"
        />
        <Spacer left=2 />
        <button
          className=[%tw
            "flex-shrink-0 bg-green-500 hover:bg-green-700
 border-green-500 hover:border-green-700 text-base border-4 text-white py-1 px-4
 rounded"
          ]
          onClick={_ => {setActualUsername(_ => Some(username))}}
          type_="button">
          "View"->React.string
        </button>
      </div>
    </div>;
  };
};

module Footer = {
  [@react.component]
  let make = () => {
    let heartEmoji: string = [%raw "'\u200D\u2764\uFE0F'"];
    <footer className=[%tw "flex sticky bottom-0"]>
      <span className="text-lg font-bold">
        {j|Made with $heartEmoji by |j}->React.string
        <a
          className="text-lg font-bold underline"
          href="https://github.com/dylanirlbeck"
          target="_blank"
          rel="noopener
 noreferrer">
          "dylanirlbeck"->React.string
        </a>
      </span>
    </footer>;
  };
};

[@react.component]
let make = () => {
  let (actualUsername, setActualUsername) = React.useState(_ => None);
  <div className=[%tw "flex flex-col h-full justify-start items-center"]>
    <Header />
    <div className="flex flex-col justify-center flex-grow">
      <Input setActualUsername />
      <Spacer bottom=12 />
      <Card username=actualUsername />
    </div>
    <Spacer bottom=48 />
    <Footer />
    <Spacer bottom=6 />
  </div>;
};
