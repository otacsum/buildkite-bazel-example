# Prescriptive CI (this branch)

This branch (`prescriptive-cicd`) intentionally contains **no `.buildkite/`
directory and no pipeline config file of any kind**.

## How CI works here

CI for this branch is defined and maintained **entirely in the Buildkite
dashboard**: a separate Buildkite Pipeline resource is pointed at this
branch, and its Steps are hardcoded directly in Pipeline Settings -> Steps
in the UI — not sourced from a file in this repo, and not generated via
`buildkite-agent pipeline upload`.

## Why

This demonstrates the **"prescriptive / mandatory-core"** governance pattern
from our CI/CD platform evaluation: because the pipeline definition is not a
file in this repository, a repo maintainer cannot alter, bypass, or extend
it through a pull request or a direct commit. Only someone with access to
the Buildkite dashboard for this pipeline can change what CI runs.

Contrast this with `main`'s **bootstrap pattern**: there, CI is repo-driven
via `.buildkite/pipeline.yml` plus a dynamic `buildkite-agent pipeline
upload`, so a repo maintainer with only GitHub write access to that branch
*can* change the CI definition by editing that file.

## Where the real pipeline definition lives

The actual Steps YAML that runs for this branch's pipeline is **not stored
in this repo** — that's the point of this branch. It is tracked externally,
in our CI platform evaluation docs, alongside the Buildkite Pipeline
resource configuration.
