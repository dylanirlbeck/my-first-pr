[@decco]
type author = {
  login: string,
  avatarUrl: string,
};

[@decco]
type repository = {name: string};

[@decco]
type node = {
  author,
  body: string,
  repository,
  title: string,
  url: string,
  state: string,
  createdAt: string,
};

[@decco]
type nodes = {nodes: array(node)};

[@decco]
type pullRequests = {pullRequests: nodes};

[@decco]
type response = {user: pullRequests};

type pullRequest = {
  repoName: string,
  body: string,
  avatarUrl: string,
  title: string,
  url: string,
  state: string,
  date: string,
};

let decode = (response: Js_json.t): pullRequest => {
  let pr = response_decode(response) |> Belt.Result.getExn;
  {
    repoName: pr.user.pullRequests.nodes[0].repository.name,
    body: pr.user.pullRequests.nodes[0].body,
    avatarUrl: pr.user.pullRequests.nodes[0].author.avatarUrl,
    title: pr.user.pullRequests.nodes[0].title,
    url: pr.user.pullRequests.nodes[0].url,
    state: pr.user.pullRequests.nodes[0].state,
    date: pr.user.pullRequests.nodes[0].createdAt,
  };
};
