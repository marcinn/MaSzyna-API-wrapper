# Contributing

## Request for changes/ Pull Requests
You first need to create a fork of this repository to commit your changes to it. Methods to fork a repository can be found in the [GitHub Documentation](https://docs.github.com/en/get-started/quickstart/fork-a-repo).

## Choose a base branch
Before starting development, you need to know which branch to base your modifications/additions on. When in doubt, use master.

| Type of change                |           | Branches              |
| :------------------           |:---------:| ---------------------:|
| Documentation                 |           | `master`              |
| Bug fixes                     |           | `master`              |
| New features                  |           | `master`              |
| New issues models             |           | `master` |

```sh
# Switch to the desired branch
git switch master

# Pull down any upstream changes
git pull

# Create a new branch to work on
git switch --create dev/[feature-or-fix-name]
```

Commit your changes, then push the branch to your fork with `git push -u fork` and open a pull request on the base repository.

Your code style must comply with [our Code style](CODE_STYLE.md) and pass CI/CD checks in order for your contribution to be merged