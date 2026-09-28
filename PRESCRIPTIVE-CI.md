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

## Safe extensibility: `.buildkite-extensions.yml`

The one exception to "nothing in this repo affects CI" is a single,
narrowly-scoped file a repo maintainer *is* allowed to add:
`.buildkite-extensions.yml`. This is **not** Buildkite pipeline YAML — it's
a small, strictly-validated schema, interpreted by a platform-owned step
(`Load Extensions`) that runs as part of the mandatory dashboard pipeline
on every build.

Schema:

```yaml
jobs:
  - name: "job-name"        # required, must match ^[a-z0-9-]{1,40}$
    commands:                # required, non-empty list of shell commands
      - "echo hello"
    timeout_minutes: 5       # optional, clamped to 1-10, default 5
    soft_fail: false         # optional, default false
```

Constraints, enforced by the interpreter, not by convention:

- **Max 3 jobs** per file, to protect the Buildkite free tier's 10-concurrent-job
  ceiling.
- **Only** `name`, `commands`, `timeout_minutes`, and `soft_fail` are
  accepted keys. No `plugins`, `agents`, `depends_on`, or `key` — those are
  exactly the levers that would let a maintainer reorder around the
  mandatory core, request a different execution environment, or collide
  with a reserved step. There is nothing here that lets an extension job
  touch, skip, or reorder `build`, `test`, the static-analysis steps, or
  `status`.
- **Fail loud, not silent.** A malformed or non-compliant file fails the
  build with a specific, actionable error annotation naming exactly what's
  wrong — it never gets silently ignored or partially applied.
- **Bypass-resistant by construction, not by convention.** Every generated
  job's step key is prefixed `ext-`, so an extension can never collide with
  a core step's key regardless of what name a maintainer picks — this isn't
  enforced by checking names against a reserved list, it's structurally
  impossible.

This is the concrete "safe extension" half of the mandatory-core-plus-extension
pattern from our platform evaluation: the core (build, test, static analysis,
status) stays entirely dashboard-defined and untouchable by a repo commit;
this file can only *add* independent, sandboxed jobs alongside it. See
`.buildkite-extensions.yml` in this repo for a live example.
