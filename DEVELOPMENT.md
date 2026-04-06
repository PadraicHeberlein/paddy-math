# 🛠️ Development Guidelines: Mirroring Library Logic in CLI

To ensure the **PaddyMath** project remains user-friendly, any new mathematical functionality added to the core library MUST be reflected in the CLI tool.

## 📋 Synchronization Rule
Whenever you add a new function (e.g., `sin`, `log`, or a new `Matrix` transformation) to `include/algebra_functions.hpp`:
1.  Open `tools/pm-cli.cpp`.
2.  Add a corresponding **subcommand** or **option** that exposes this function to the user.
3.  Update the CLI specific help strings to include the new capability.

## 🚀 How to Add a New Subcommand
For example, if you add `sin_taylor(const T& x)` to the library:

1.  Find the relevant subcommand group (e.g., `complex_cmd` or `matrix_cmd`).
2.  Add it as a sub-action or a new flag:
    ```cpp
    auto sin_cmd = app.add_subcommand("sin", "Calculate sine via Taylor series");
    // Reuse input logic for types...
    sin_cmd->callback([&]() {
        // ... call sin_taylor(x) ...
    });
    ```

## 🧪 Testing the Mirroring
After adding the CLI functionality:
-   Run `make pm-cli` in your build directory.
-   Verify the output using `./pm-cli <command> --help`.
-   Perform a manual verification of the calculation.

---
*Follow these steps to keep the PaddyMath CLI and library in sync!*
