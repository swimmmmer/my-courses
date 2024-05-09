;; Name: Javeria Hanif
;; Date: Mar 26, 2024
;; Course: CMSC 403 Spring 2024
;; Description: The Assignment6.lisp file serves as practice to become familiar with the syntax and function definitions of Common Lisp. 
;; I defined individual functions and practiced using list operations, optional variables, function, variable, and macro definitions. 

(defun newList ()
 (cons 3 (cons 4 (cons 5 nil))))

;; (3 4 5)

(defun L () 
 (cons 4 
    (cons "s" 
        (list 6))))

 ;; ( 4 "s" (6))



;; myList function
(defun myList ()
  "Creates and returns a list"
  ;; first element is 4
  (cons 4 
        ;; next elements in the list is (7 22)
        (cons (cons 7 (cons 22 nil))
            ;; next element in the list is a string "art" 
              (cons "art" 
                    ;; next elements in the list are ("math" (8) 99) 100)
                    (cons (cons "math" (cons (list 8) (cons 99 nil)))
                          (list 100))))))

;; leapYear function
(defun leapYear () 
    "Returns an ordered list of leaps years between 1800-2021"
    ;; loops iterates over years from 1800 - 2021
    (loop for year from 1800 to 2021
        ;; checks if the year is a leap year
        when (or (= 0 (mod year 400)) ;; checks if leap year is divisible by 400
            (and (not (= 0 (mod year 100))) ;; checks if leap year is NOT divisible by 100
                (= 0 (mod year 4)))) ;; checks if leap year is divisible by 4
        ;; collects the leap years
        collect year))

;; union- function
(defun union- (list1 list2)
    "Computes a union of two list without any duplication"
     ;; concatenates list1 and list2 and removes duplicates
    (remove-duplicates (append list1 list2)))

;; avg function
(defun avg (aList &optional (sum 0) (count 0))
    "Computes the average of elements in aList"
    (if (null aList) ;; checks if the list is empty
        (if (zerop count) ;; checks if the count is 0 
            nil ;; returns nil 
            (/ sum count)) ;; caclulates the average
        (if (numberp (car aList)) ;; checks if first element of the list is a number 
            (avg (cdr aList) ;; returns rest of the elements in the list
            (incf sum (car aList)) ;; increments sum by adding the first element
            (incf count)) ;; increments the count 
            (avg (cdr aList) sum count)))) ;; returns rest of the elements in the list

;; isType function
(defun isType (dataType)
    "Returns a value that matches the specified data type"
    (lambda (value) 
        (if (typep value dataType) ;; checks if the value is of type dataType
            T))) ;; returns true 

;; taxCalculator function
(defun taxCalculator (limit rate values &optional result) ;; defines result as an optional parameter
    "Calculates the given values"
    (if (and (numberp limit) (numberp rate) (listp values)) ;; checks if limit and rate are numbers, and values are in a list
        (if (null values) ;; checks if values are null
            (nreverse (or result '())) ;; then returns the result in reverse order or an empty list 
            (let ((num (car values))) ;; initializes first elements of the list as num 
            (if (numberp num) ;; checks if elements in the list are numbers 
                (if (> num limit) ;; checks if num is greater than limit
                    (taxCalculator limit rate (cdr values) (cons (* num rate) result)) ;; computes rate if num > limit and returns it as a result
                    (taxCalculator limit rate (cdr values) (cons num result))) ;; returns result if num is not bigger than limit
                (taxCalculator limit rate (cdr values) result)))) ;; returns rest of the values
        nil)) ;; returns nil

;; clean function 
(defun aFunc (f)
  "Checks if the argument is a number."
  (numberp f))

(defun clean (aFunc aList)
  "Filters elements from aList based on whether aFunc returns true for each element."
  (if (null aList)
      nil ;; returns nil for an empty list
      (if (listp (car aList)) ;; checks if first element is a list
          (cons (clean aFunc (car aList)) (clean aFunc (cdr aList))) ;; recursively filters sublists by using clean on elements of the list
          (if (funcall aFunc (car aList)) ;; checks if the first element is true (when passed to aFunc)
              (cons (car aList) (clean aFunc (cdr aList))) ;; adds the first element to the result list if returned true by aFunc
              (clean aFunc (cdr aList)))))) ;; skips the element otherwise

;; threeWayBranch function
(defmacro threeWayBranch (x y z)
    "Evaluates the x y z conditions"
    `(if ,(car x) (progn ,@(cdr x)) ;; if x condtion is true, then executes the rest of x 
        (if ,(car y) (progn ,@(cdr y)) ;; or if y condtion is true, then executes the rest of y
            (if ,(car z) (progn ,@(cdr z)) ;; or if z condtion is true, then executes the rest of z
                nil)))) ;; returns nil otherwise
