# Publishing from a local Linux checkout

1. Install `git`, `make`, a C compiler, and GitHub CLI (`gh`). On Arch:

```sh
sudo pacman -S --needed git github-cli base-devel
```

2. Authenticate from your own terminal if not already logged in:

```sh
gh auth login
```

3. Review source tree and `LICENSE`. Keep proprietary files out.

```sh
cd /src/open-carps2
make test
./scripts/publish-github.sh
```

The publishing script asks before creating the **public** GitHub repository
`kevito666/open-carps2`, and pushes only an explicit list of project files.
If the GitHub repository already exists, or `origin` is already defined, it stops
rather than rewriting it.

After the repository is created, it can be edited using the connected GitHub tools.

If you actually wanted `~/src/open-carps2` (under your home directory), pass that path
as the argument to the separate setup script; the publish step works in either place.
