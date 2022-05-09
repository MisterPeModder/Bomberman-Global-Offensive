## How to contribute

#### **Did you find a bug?** / **Do you want to suggest somthing?**

* Create an issue at [this issue page](https://github.com/MisterPeModder/Bomberman/issues).

#### **Do you want to fix an issue?**

* Create a branch formatted as `fix/<ISSUENUMBER>-<TITLE>` for bug fixes or `feature/<ISSUENUMBER>-<TITLE>` for features, example: `fix/4221-infinite-loop`.

* Submit a [pull request](https://github.com/MisterPeModder/Bomberman/pulls).

* Once validated, merge to PR to `master` and remove the source branch (with `git branch -D <branch_name>`.

### ***How to title commits?***

* Follow the guidelines at https://cbea.ms/git-commit/

* Use imperative tense (avoid past tense).

* The title of the commit must be a summuary of the content and not be too long (less than 50 characters).

* Prefer putting detailed informations inside the commit's description.

* Example:
  ```sh
  $> git commit -m 'Fix infinite loop when pressing Alt-F4
  
  This was caused by a missing check in the event loop
  The program now checks when the window is set to close'
  ```

#### **DOs and DONTs**

* :x: **DONT**: Push to the `master` (or `main`) branch for any reason, please submit a PR instead.

* :x: **DONT**: Create a branch with your username as the title

* :heavy_check_mark: **DO**: Commit often! allows everyone to see your progress and eventually make suggestions on it.

* :heavy_check_mark: **DO**: Format your code, using either `clang-format` directly or your IDE's capabilities (and yes, VSCode can format your code for you!)

***

Thanks! :heart: :heart: :heart:
