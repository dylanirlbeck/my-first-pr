let makeQuery = username => {j|
  query pullRequests {
    user(login:"$username") {
      pullRequests(first:1) {
        nodes {
          author {
            login
          }
          repository {
            name
          }
          body
        }
      }
    }
  }
|j};

let authToken = [%raw "process.env.AUTH_TOKEN"];

let headers =
  Fetch.HeadersInit.makeWithArray([|
    ("Content-type", "application/json"),
    ("Accept", "application/json"),
    ("Authorization", "bearer " ++ authToken),
  |]);

exception Graphql_error(string);

let sendQuery = (~query) =>
  Fetch.(
    fetchWithInit(
      "https://api.github.com/graphql",
      RequestInit.make(
        ~method_=Post,
        ~body=
          Js.Dict.fromList([("query", Js.Json.string(query))])
          |> Js.Json.object_
          |> Js.Json.stringify
          |> BodyInit.make,
        ~headers,
        (),
      ),
    )
    |> Js.Promise.then_(resp =>
         if (Response.ok(resp)) {
           Response.json(resp)
           |> Js.Promise.then_(data =>
                switch (Js.Json.decodeObject(data)) {
                | Some(obj) =>
                  Js.Dict.unsafeGet(obj, "data") |> Js.Promise.resolve
                | None =>
                  Js.Promise.reject(
                    Graphql_error("Response is not an object"),
                  )
                }
              );
         } else {
           Js.Promise.reject(
             Graphql_error("Request failed: " ++ Response.statusText(resp)),
           );
         }
       )
  );

type pullRequest = {
  repoName: string,
  body: string,
  date: Js.Date.t,
  merged: bool,
  url: string,
};
