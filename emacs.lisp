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

(setq default-frame-alist '((height . 45) (width . 90) (menu-bar-lines . 20) (tool-bar-lines . 0)))
(tool-bar-mode 0)
(setq backup-directory-alist (quote (("." . "~/.backups"))))

(ido-mode t)
(global-set-key (kbd "M-x") 'smex)

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

;;(autoload 'w3m "w3m" "interface for w3m on emacs" t)
;;(setq w3m-command-arguments '("-cookie" "-F"))
;;(setq w3m-use-cookies t)
;;(setq w3m-home-page "http://www.baidu.com/")
;;(require 'mime-w3m)
;;(setq w3m-default-display-inline-image t)
;;(setq w3m-default-toggle-inline-images t)

(scroll-bar-mode 0)
;;(add-hook 'prog-mode-hook #'rainbow-delimiters-mode)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(ansi-color-faces-vector
   [default default default italic underline success warning error])
 '(blink-cursor-mode nil)
 '(column-number-mode t)
 '(cua-mode t nil (cua-base))
 '(custom-enabled-themes (quote (spacemacs-dark)))
 '(custom-safe-themes
   (quote
	("bffa9739ce0752a37d9b1eee78fc00ba159748f50dc328af4be661484848e476" default)))
 '(display-time-mode t)
 '(inhibit-startup-screen t)
 '(package-selected-packages (quote (spacemacs-theme rainbow-delimiters)))
 '(show-paren-mode t)
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:family "Fantasque Sans Mono" :foundry "PfEd" :slant normal :weight normal :height 113 :width normal)))))

(add-hook 'prog-mode-hook #'rainbow-delimiters-mode)
