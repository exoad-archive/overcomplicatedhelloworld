> ; first cell empty
;; Source: https://codegolf.stackexchange.com/a/16866
;; All the chars made in a generic way
;; by first adding the modulus of char by
;; 16 and then adding mutiples of 16
;; This simplifies adding more characters 
;; for later versions
------>>++++[-<++++>]<[-<+>]        ; CR
+>>++++[-<++++>]<[-<++>]            ; !
++++>>++++[-<++++>]<[-<++++++>]     ; d
---->>++++[-<++++>]<[-<+++++++>]    ; l
++>>++++[-<++++>]<[-<+++++++>]      ; r
->>++++[-<++++>]<[-<+++++++>]       ; o
+++++++>>++++[-<++++>]<[-<+++++++>] ; w
>>++++[-<++++>]<[-<++>]             ; space
---->>++++[-<++++>]<[-<+++>]        ; comma
->>++++[-<++++>]<[-<+++++++>]       ; o
---->>++++[-<++++>]<[-<+++++++>]    ; l
---->>++++[-<++++>]<[-<+++++++>]    ; l
+++++>>++++[-<++++>]<[-<++++++>]    ; e
-------->>++++[-<++++>]<[-<+++++++>]; h
<[.<] ; print until the first empty cell
