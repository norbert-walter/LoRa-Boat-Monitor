## Motivation

This pull request adds **Dev Container support** to the project, enabling
browser-based and reproducible development using **code-server** or
**VS Code Dev Containers**.

This allows users to:
- open the repository directly in a web browser
- work without local toolchain installation
- build the project using PlatformIO in a containerized environment

The change is fully optional and does not affect existing local workflows.

---

## What’s included

- A `.devcontainer/` configuration describing the development environment
- Automatic installation of PlatformIO
- VS Code / code-server integration
- No server-specific or platform-specific configuration

---

## What’s NOT included

- No authentication or password handling
- No USB or upload port assumptions
- No docker-compose or server configuration

These aspects are intentionally left to the hosting environment.

---

## How to use

1. Open the repository in a Dev Container–enabled environment
   (e.g. code-server or VS Code Dev Containers)
2. Wait for the container to initialize
3. Build the project using PlatformIO
4. Upload to an ESP32 if USB access is available

---

## Compatibility

- Existing local PlatformIO workflows remain unchanged
- Works with GitHub Codespaces–style environments
- No changes to source code logic
