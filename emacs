(global-set-key "\C-m" 'newline-and-indent)
(global-set-key (kbd "C-<return>") 'newline)
(show-paren-mode t)
(setq column-number-mode t)
(setq line-number-mode t)
;;(setq-default cursor-type 'bar)
(setq-default tab-width 4)
(setq tab-width 4 indent-tabs-mode t c-basic-offset 4)
(setq auto-image-file-mode t)
(setq display-time-day-and-date t)
(display-time-mode 1)
(global-hl-line-mode t)
;;(electric-pair-mode t)
(set-frame-parameter (selected-frame) 'alpha (list 85 85))
(add-to-list 'default-frame-alist (cons 'alpha(list 85 85)))
(global-linum-mode t)
(cua-mode t)

(setq default-frame-alist '((height . 50) (width . 90) (menu-bar-lines . 20) (tool-bar-lines . 0)))

(setq backup-directory-alist (quote (("." . "~/.backups"))))

(require 'package)
(add-to-list 'package-archives 
             '("melpa" . "http://melpa.org/packages/"))
(package-initialize)

(defun compile-file ()
  (interactive)
  (compile (format "g++ -o %s %s -g "  (file-name-sans-extension (buffer-name))(buffer-name))))
(defun compile-file-O2 ()
  (interactive)
  (compile (format "g++ -o %s %s -g -O2"  (file-name-sans-extension (buffer-name))(buffer-name))))
;;;;;设置一键调试
(global-set-key [f7] 'gud-gdb)
(global-set-key [f9] 'compile-file)
(global-set-key [f10] 'compile-file-O2)
;;;;;改变emacs标题栏的标题
(setq frame-title-format "Exbilar's %b")

(setq ring-bell-function 'ignore)

;;;;;指针不要闪，我得眼睛花了
(blink-cursor-mode -1)
;;;;;滚动页面时比较舒服，不要整页的滚动
(setq scroll-step 1
        scroll-margin 3
        scroll-conservatively 10000)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(ansi-color-faces-vector
   [default default default italic underline success warning error])
 '(ansi-color-names-vector
   ["#0a0814" "#f2241f" "#67b11d" "#b1951d" "#4f97d7" "#a31db1" "#28def0" "#b2b2b2"])
 '(blink-cursor-mode nil)
 '(column-number-mode t)
 '(cua-mode t nil (cua-base))
 '(custom-enabled-themes (quote (spacemacs-dark)))
 '(custom-safe-themes
   (quote
	("ff7625ad8aa2615eae96d6b4469fcc7d3d20b2e1ebc63b761a349bebbb9d23cb" "fa2b58bb98b62c3b8cf3b6f02f058ef7827a8e497125de0254f56e373abee088" "946e871c780b159c4bb9f580537e5d2f7dba1411143194447604ecbaf01bd90c" "158013ec40a6e2844dbda340dbabda6e179a53e0aea04a4d383d69c329fba6e6" "2b8dff32b9018d88e24044eb60d8f3829bd6bbeab754e70799b78593af1c3aba" "256a381a0471ad344e1ed33470e4c28b35fb4489a67eb821181e35f080083c36" "bffa9739ce0752a37d9b1eee78fc00ba159748f50dc328af4be661484848e476" default)))
 '(display-time-mode t)
 '(inhibit-startup-screen t)
 '(package-selected-packages
   (quote
	(cdlatex latex-math-preview auctex multiple-cursors dracula-theme sml-mode all-the-icons-dired xwidgete auto-complete rainbow-blocks rainbow-mode spaceline-all-the-icons spacemacs-theme ws-butler winum which-key wgrep volatile-highlights vi-tilde-fringe uuidgen use-package toc-org spaceline smex restart-emacs request rainbow-delimiters popwin persp-mode pcre2el paradox org-plus-contrib org-bullets open-junk-file neotree move-text mmm-mode markdown-toc macrostep lorem-ipsum linum-relative link-hint ivy-hydra info+ indent-guide hungry-delete hl-todo highlight-parentheses highlight-numbers highlight-indentation hide-comnt help-fns+ helm-make google-translate golden-ratio gh-md flx-ido fill-column-indicator fancy-battery eyebrowse expand-region exec-path-from-shell evil-visualstar evil-visual-mark-mode evil-unimpaired evil-tutor evil-surround evil-search-highlight-persist evil-numbers evil-nerd-commenter evil-mc evil-matchit evil-lisp-state evil-indent-plus evil-iedit-state evil-exchange evil-escape evil-ediff evil-args evil-anzu eval-sexp-fu elisp-slime-nav dumb-jump define-word counsel-projectile column-enforce-mode clean-aindent-mode auto-highlight-symbol auto-compile aggressive-indent adaptive-wrap ace-window ace-link))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

(put 'upcase-region 'disabled nil)

;;(autoload 'w3m "w3m" "interface for w3m on emacs" t)
;;(setq w3m-command-arguments '("-cookie" "-F"))
;;(setq w3m-use-cookies t)
;;(setq w3m-home-page "http://www.baidu.com/")
;;(require 'mime-w3m)
;;(setq w3m-default-display-inline-image t)
;;(setq w3m-default-toggle-inline-images t)

;;bash

(setq shell-file-name "/bin/bash")
(autoload 'ansi-color-for-comint-mode-on "ansi-color" nil t) 
(add-hook 'shell-mode-hook 'ansi-color-for-comint-mode-on t)

(scroll-bar-mode 0)
(add-hook 'prog-mode-hook #'rainbow-delimiters-mode)
