# Catsxp Browser - Partial Open Source Components
# Catsxp 浏览器 - 部分开源组件

**Core Open-Sourced Features: New Tab Page, Ad Blocking, Tab Container, Keyboard Shortcuts & Sync Chain**
**核心开源功能：新标签页、广告过滤、标签容器、快捷键 & 同步链**

[English](#english) | [中文](#中文)

---

## English

### Overview

The main body of Catsxp Browser is proprietary and closed-source. This repository **solely** contains the source code of five core components that have been modified from upstream MPL 2.0 projects and are distributed under the **Mozilla Public License 2.0 (MPL 2.0)** :

-   **New Tab Page** (新标签页)
-   **Ad Blocking** (广告过滤)
-   **Tab Container** (标签容器)
-   **Keyboard Shortcuts** (快捷键)
-   **Sync Chain** (同步链)

**This repository does NOT contain the complete source code of Catsxp Browser.** All other proprietary code remains closed-source and is not provided here.

### Original Upstream Source

These components are based on code from the following open-source projects:

| Component | Original Project | Upstream Repository |
| :--- | :--- | :--- |
| New Tab Page | Brave Browser | https://github.com/brave/brave-core |
| Ad Blocking | Brave Browser | https://github.com/brave/brave-core |
| Tab Container | Brave Browser | https://github.com/brave/brave-core |
| Keyboard Shortcuts | Brave Browser | https://github.com/brave/brave-core |
| Sync Chain | Brave Browser | https://github.com/brave/brave-core |

All original code is copyright © Brave Software, Inc. and its contributors, licensed under MPL 2.0.

### L - License Compliance

I respect open-source licenses. The code in this repository is provided to comply with MPL 2.0 obligations.

-   **What is open:**
    -   Modified MPL 2.0 files related to the **New Tab Page** functionality.
    -   Modified MPL 2.0 files related to the **Ad Blocking / Filtering** functionality.
    -   Modified MPL 2.0 files related to the **Tab Container** functionality.
    -   Modified MPL 2.0 files related to the **Keyboard Shortcuts** functionality.
    -   Modified MPL 2.0 files related to the **Sync Chain** functionality.
-   **What is NOT open:**
    -   All other independently created code, including UI integration logic, proprietary features, build scripts, and the core browser shell. These remain closed-source and are the exclusive intellectual property of 那份心情.

Each file retains its original upstream copyright notice.

### R - Responsibility Fulfilled

In compliance with MPL 2.0, this repository fulfills the following obligations:

1.  **Source Code Availability:** The upstream components from Brave have been customized and modified. All modified files are provided in this repository in full, without obfuscation or omission.
2.  **Clear Code Boundaries:** Open-source components are strictly separated from proprietary code. This repository contains only the modified files subject to MPL 2.0.
3.  **Version Correspondence:** The source code provided here corresponds exactly to the distributed binary releases.

**Statement:** This project incorporates and modifies select components from Brave Browser. All modified files are made available in this repository as required by MPL 2.0. License obligations have been fulfilled.

### Features Included in This Repository

| Feature | Description | Original Upstream |
| :--- | :--- | :--- |
| **New Tab Page** | Customized new tab experience with modified layout, widgets, and background handling. | Brave Browser (MPL 2.0) |
| **Ad Blocking** | Enhanced ad and tracker filtering engine with performance optimizations and regional rule sets. | Brave Browser (MPL 2.0) |
| **Tab Container** | Enhanced tab grouping and management with custom container logic and isolation. | Brave Browser (MPL 2.0) |
| **Keyboard Shortcuts** | Customized keyboard shortcut system with enhanced key binding management and user-defined shortcuts. | Brave Browser (MPL 2.0) |
| **Sync Chain** | Enhanced device synchronization chain with improved data sync reliability and multi-device management. | Brave Browser (MPL 2.0) |

### How to Get the Source Code

The **partial source code** for the MPL 2.0 components included in each binary release of Catsxp Browser is available in this repository under matching [Git Tags](https://github.com/catsxp/Catsxp_MPL2.0/tags).

-   This repository contains **only** the source code of modified **New Tab Page**, **Ad Blocking**, **Tab Container**, **Keyboard Shortcuts**, and **Sync Chain** components.
-   To get the component source for a specific release, clone this repository and checkout the corresponding tag.
-   The `main` branch always contains the most recently published version of these components' source.

**Note:** This repository does **NOT** contain the complete source code of Catsxp Browser. All other proprietary code is closed-source and not provided here.

### Source Code Update Frequency

**Important Notice:**

Due to limited personal resources and the fact that this project is maintained by a single developer, I **cannot guarantee** that the open-source code in this repository is always synchronized with the latest binary release in real time.

-   **Update Cycle:** I aim to update this repository on a **monthly** or **yearly** basis, depending on the significance of the changes.
-   **What This Means:** The source code available here may lag behind the latest binary version by one or more release cycles.
-   **My Commitment:** Despite the delay, I will always ensure that the source code provided corresponds to a specific, identifiable binary release. I will never provide mismatched or obfuscated code.

I appreciate your understanding of the constraints of a small-scale project.

### Important Note on Building

The source code in this repository **cannot be compiled independently**. These are component files extracted from a larger proprietary build system. I provide this source snapshot strictly for MPL 2.0 compliance.

### Third-Party Dependencies

If my modifications introduce additional third-party dependencies, they will be listed here with their respective licenses.

*Currently, no additional third-party dependencies beyond the original upstream.*

### Disclaimer

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

### Copyright Infringement Notice

I respect the intellectual property rights of others. If you believe that any content in this repository infringes upon your copyright or intellectual property rights, please contact me immediately with the following information:

1.  A description of the copyrighted work or intellectual property that you claim has been infringed.
2.  A description of where the allegedly infringing material is located in this repository (specific file path or URL).
3.  Your contact information (name, email address, and/or mailing address).
4.  A statement by you that you have a good faith belief that the disputed use is not authorized by the copyright owner, its agent, or the law.
5.  A statement by you, made under penalty of perjury, that the information in your notice is accurate and that you are the copyright owner or authorized to act on the copyright owner's behalf.

Upon receiving a valid notice, I will promptly investigate and take appropriate action, including removing or disabling access to the allegedly infringing material if necessary.

**Contact for infringement claims:** 3303118@qq.com

### Contributions

This repository exists primarily for license compliance and transparency. External pull requests for these specific components are **generally not accepted**, as they are tightly integrated with my proprietary build system.

However, bug reports and improvement suggestions are welcome via [GitHub Issues](https://github.com/catsxp/Catsxp_MPL2.0/issues).

### License

All files in this repository are licensed under **Mozilla Public License 2.0**, unless otherwise noted. See the [LICENSE](LICENSE) file for the full text.

### Contact

-   **Email:** 3303118@qq.com
-   **Project:** https://github.com/catsxp/Catsxp_MPL2.0

---
© 2020 那份心情. Some rights reserved.

---

## 中文

### 概述

Catsxp 浏览器主体为闭源软件。本仓库**仅**包含从上游 MPL 2.0 项目修改而来的五个核心组件的源代码，基于 **Mozilla Public License 2.0 (MPL 2.0)** 分发：

-   **新标签页** (New Tab Page)
-   **广告过滤** (Ad Blocking)
-   **标签容器** (Tab Container)
-   **快捷键** (Keyboard Shortcuts)
-   **同步链** (Sync Chain)

**本仓库不包含 Catsxp 浏览器的完整源代码。** 所有其他专有代码均为闭源，不在本仓库提供。

### 原始上游出处

这些组件基于以下开源项目的代码：

| 组件 | 原始项目 | 上游仓库 |
| :--- | :--- | :--- |
| 新标签页 | Brave 浏览器 | https://github.com/brave/brave-core |
| 广告过滤 | Brave 浏览器 | https://github.com/brave/brave-core |
| 标签容器 | Brave 浏览器 | https://github.com/brave/brave-core |
| 快捷键 | Brave 浏览器 | https://github.com/brave/brave-core |
| 同步链 | Brave 浏览器 | https://github.com/brave/brave-core |

所有原始代码版权归 © Brave Software, Inc. 及其贡献者所有，基于 MPL 2.0 许可。

### L - 许可证合规

我尊重开源许可证。本仓库代码为履行 MPL 2.0 义务而提供。

-   **开源范围：**
    -   与**新标签页**功能相关的、修改过的 MPL 2.0 文件。
    -   与**广告过滤/拦截**功能相关的、修改过的 MPL 2.0 文件。
    -   与**标签容器**功能相关的、修改过的 MPL 2.0 文件。
    -   与**快捷键**功能相关的、修改过的 MPL 2.0 文件。
    -   与**同步链**功能相关的、修改过的 MPL 2.0 文件。
-   **闭源范围：**
    -   所有其他独立创建的代码，包括 UI 集成逻辑、专有功能、构建脚本和核心浏览器框架。这些保持闭源，是 那份心情 的独家知识产权。

每个文件均保留原始上游版权声明。

### R - 义务履行完毕

基于 MPL 2.0 协议要求，本仓库已履行以下义务：

1.  **提供修改后的源代码：** 本项目对 Brave 上游组件进行了定制化修改。所有修改过的文件均已在本仓库中完整提供，未作任何混淆或删减。
2.  **保持代码边界清晰：** 开源组件与闭源代码严格隔离，本仓库仅包含受 MPL 2.0 协议约束的修改文件。
3.  **确保版本对应：** 本仓库提供的源代码与已分发的二进制版本严格对应。

**声明：** 本项目使用了 Brave 浏览器的部分组件代码，并在此基础上进行了修改。所有修改后的文件均已按 MPL 2.0 协议要求在本仓库开源。许可证义务已履行完毕。

### 本仓库包含的功能

| 功能 | 说明 | 原始上游项目 |
| :--- | :--- | :--- |
| **新标签页** | 定制化的新标签页体验，包含修改过的布局、小部件和背景处理。 | Brave 浏览器 (MPL 2.0) |
| **广告过滤** | 增强的广告和追踪器过滤引擎，包含性能优化和区域性规则集。 | Brave 浏览器 (MPL 2.0) |
| **标签容器** | 增强的标签页分组和管理功能，包含自定义容器逻辑和隔离机制。 | Brave 浏览器 (MPL 2.0) |
| **快捷键** | 定制化的键盘快捷键系统，包含增强的按键绑定管理和用户自定义快捷键功能。 | Brave 浏览器 (MPL 2.0) |
| **同步链** | 增强的设备同步链功能，包含改进的数据同步可靠性和多设备管理能力。 | Brave 浏览器 (MPL 2.0) |

### 如何获取源代码

Catsxp 浏览器各发布版本中，**MPL 2.0 组件的部分源代码**，可通过本仓库的 [Git Tags](https://github.com/catsxp/Catsxp_MPL2.0/tags) 获取。

-   本仓库**仅**包含从上游 MPL 2.0 项目修改而来的**新标签页**、**广告过滤**、**标签容器**、**快捷键**和**同步链**组件的源代码。
-   如需获取特定版本对应的组件源码，请克隆本仓库并检出对应标签。
-   `main` 分支始终包含最新已发布版本中这些组件的源代码。

**请注意：** 本仓库**不包含** Catsxp 浏览器的完整源代码。所有其他专有代码均为闭源，不在本仓库提供。

### 源码更新频率

**重要提示：**

由于个人精力有限，且本项目由单人维护，我**无法承诺**本仓库的开源代码始终与最新的二进制版本实时同步。

-   **更新周期：** 我尽力以**每月**或**每年**的频率更新本仓库，具体视改动的重要程度而定。
-   **这意味着：** 此处提供的源代码，可能会落后于最新的二进制版本一个或多个发布周期。
-   **我的承诺：** 尽管存在延迟，我始终确保所提供的源代码对应某个具体的、可辨识的二进制发布版本。我永远不会提供不匹配或混淆过的代码。

感谢你理解小型项目的现实限制。

### 关于编译的重要说明

本仓库中的源代码**无法独立编译**。这些是修改后的组件文件，需集成到更大的闭源构建系统中才能运行。我提供此源码快照，仅用于满足 MPL 2.0 合规要求。

### 第三方依赖

如果我的修改引入了额外的第三方依赖，将在此处列出及其对应许可证。

*目前，除原始上游外，未引入额外的第三方依赖。*

### 免责声明

本软件按"原样"提供，不提供任何明示或暗示的保证，包括但不限于对适销性、特定用途适用性和不侵权的保证。在任何情况下，作者或版权持有人均不对因软件或软件的使用或其他交易中产生的任何索赔、损害或其他责任负责。

### 侵权申诉

我尊重他人的知识产权。如果你认为本仓库中的任何内容侵犯了你的版权或知识产权，请立即通过以下信息联系我：

1.  你声称被侵权的版权作品或知识产权的描述。
2.  你声称侵权内容在本仓库中的具体位置（文件路径或 URL）。
3.  你的联系方式（姓名、邮箱地址和/或邮寄地址）。
4.  你基于善意相信该有争议的使用未经版权所有人、其代理人或法律授权的声明。
5.  你在承担伪证责任的前提下，声明你通知中的信息准确无误，且你是版权所有人或被授权代表版权所有人行事。

在收到有效通知后，我将及时调查并采取适当措施，包括在必要时移除或禁止访问涉嫌侵权的内容。

**侵权申诉联系方式：** 3303118@qq.com

### 贡献说明

本仓库主要用于许可证合规和透明度目的。由于这些组件与我的闭源构建系统紧密集成，**通常不接受**外部拉取请求 (Pull Request)。

但是，欢迎通过 [GitHub Issues](https://github.com/catsxp/Catsxp_MPL2.0/issues) 提交 Bug 报告和改进建议。

### 许可证

除非文件头部另有声明，本仓库所有文件均基于 **Mozilla Public License 2.0** 许可。完整文本见 [LICENSE](LICENSE) 文件。

### 联系方式

-   **邮箱：** 3303118@qq.com
-   **项目：** https://github.com/catsxp/Catsxp_MPL2.0

---
© 2020 那份心情. 部分权利保留。
