;;; doom-modeline-autoloads.el --- automatically extracted autoloads
;;
;;; Code:
(add-to-list 'load-path (directory-file-name (or (file-name-directory #$) (car load-path))))

;;;### (autoloads nil "doom-modeline" "doom-modeline.el" (24097 32053
;;;;;;  498054 829000))
;;; Generated autoloads from doom-modeline.el

(autoload 'doom-modeline-init "doom-modeline" "\
Initialize doom mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-main-modeline "doom-modeline" "\
Set main mode-line.
If DEFAULT is non-nil, set the default mode-line for all buffers.

\(fn &optional DEFAULT)" nil nil)

(autoload 'doom-modeline-set-minimal-modeline "doom-modeline" "\
Set minimal mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-special-modeline "doom-modeline" "\
Set sepcial mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-project-modeline "doom-modeline" "\
Set project mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-vcs-modeline "doom-modeline" "\
Set vcs mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-info-modeline "doom-modeline" "\
Set Info mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-package-modeline "doom-modeline" "\
Set package mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-media-modeline "doom-modeline" "\
Set media mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-message-modeline "doom-modeline" "\
Set message mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-pdf-modeline "doom-modeline" "\
Set pdf mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-timemachine-modeline "doom-modeline" "\
Set timemachine mode-line.

\(fn)" nil nil)

(autoload 'doom-modeline-set-helm-modeline "doom-modeline" "\
Set helm mode-line.

\(fn &rest _)" nil nil)

(defvar doom-modeline-mode nil "\
Non-nil if Doom-Modeline mode is enabled.
See the `doom-modeline-mode' command
for a description of this minor mode.
Setting this variable directly does not take effect;
either customize it (see the info node `Easy Customization')
or call the function `doom-modeline-mode'.")

(custom-autoload 'doom-modeline-mode "doom-modeline" nil)

(autoload 'doom-modeline-mode "doom-modeline" "\
Toggle doom-modeline on or off.

\(fn &optional ARG)" t nil)

;;;***

;;;### (autoloads nil "doom-modeline-env" "doom-modeline-env.el"
;;;;;;  (24097 32053 494481 347000))
;;; Generated autoloads from doom-modeline-env.el
 (autoload 'doom-modeline-env-setup-python "doom-modeline-env")
 (autoload 'doom-modeline-env-setup-ruby "doom-modeline-env")
 (autoload 'doom-modeline-env-setup-perl "doom-modeline-env")
 (autoload 'doom-modeline-env-setup-go "doom-modeline-env")
 (autoload 'doom-modeline-env-setup-elixir "doom-modeline-env")
 (autoload 'doom-modeline-env-setup-rust "doom-modeline-env")

;;;***

;;;### (autoloads nil nil ("doom-modeline-core.el" "doom-modeline-pkg.el"
;;;;;;  "doom-modeline-segments.el") (24097 32053 499794 270000))

;;;***

;; Local Variables:
;; version-control: never
;; no-byte-compile: t
;; no-update-autoloads: t
;; End:
;;; doom-modeline-autoloads.el ends here
