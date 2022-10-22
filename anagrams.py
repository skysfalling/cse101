
# ====================== ANAGRAMS ======================
def all_perms(elements):
    #print(">> input", elements)
  
    #base case, make sure input is greater than one
    if len(elements) <=1:
        #print("return")
        return elements
    #else, find anagrams of base case
    else:
        #print ("DELETE LIST")

        # create temp string
        tmp = []

        # for each subset in word
        #print(":: for loop ::")
        for perm in all_perms(elements[1:]):
            #print("++ elements =", elements)

            # for each char in word, find anagram
            #print(">>>> perm :", perm)
            for i in range(len(elements)):

                #slice first part of word, insert first letter of recursion word, slice last part of word
                tmp.append(perm[:i] + elements[0:1] + perm[i:])

                #print("     firsthalf:", perm[:i], "top:" , elements[0:1], "secondhalf:", perm[i:])
                #print("---- append:", perm[:i] + elements[0:1] + perm[i:] )
        #print("curr tmp:", tmp, "\n")
        return tmp

def rec_anagrams(stack):
  #print("stack:", stack)
  stack_len = len(stack)
  
  if stack_len <= 1:
    return stack;
  else:

    # remove top value from stack for recursion
    top = stack[0]
    stack = stack[1:]
    list = rec_anagrams(stack)
    out = []

    # for each anagram in list
    for anagram in list:
      #print("anagram: ", anagram)
      # for each char in stack, find anagram
      for i in range(stack_len):
        #print("curr stack : ", stack)
        a = anagram[:i] + top + anagram[i:]
        out.append(a)

    #print("curr out:", out, "\n")
    return out;

def anagrams(in_str):

  # create init stack
  stack = []
  for c in in_str:
    stack.append(c)
  print("init stack", stack)
  
  # init final out list
  list = [stack[-1]]

  #anagram size
  a_size = 1;
  
  while (a_size < len(in_str)):
    # remove top value from stack for recursion
    top = stack[0]
    print("++++ top :", top)
    
    a_size += 1
    print("++++ a_size :", a_size)
    
    stack = stack[1:]
    out = []

    # for each anagram in list
    for anagram in list:
      print("-- anagram: ", anagram)
      # for each char in stack, find anagram
      for i in range(a_size):
        a = anagram[:i] + top + anagram[i:]
        out.append(a)

    list = out
    print("curr list:", list, "\n")

  list.sort()
  print("\nfinal list:", list)
  return list;
  
    

p = all_perms("dcba")
p.sort()
#print("p:", p)

stack = ["d", "c", "b", "a"]
a = rec_anagrams(stack)
a.sort()
#print ("a:", a)

anagrams("abcd")


# ===================== LANGUAGE =======================

class Pair:
  in_str = ""
  fixed_str = ""

def language(in_str, k):
  print("\n==== LANGUAGE =====")
  out_list = [""]
  temp_stack = [] # resets every loop
                  # saves last round of 
  tmp_holder = []
  
  fixed_stack = [] # save original stack

  #base case
  if k != 0:
    # push all characters to stack
    for i in range(len(in_str)):
      fixed_stack.append(in_str[i])
      out_list.append(in_str[i])

    tmp_holder = fixed_stack

    # loop
    for loop in range(k - 1):
      print("\ntemp_holder: ", tmp_holder)
      temp_stack = tmp_holder
      tmp_holder = []
      # create combinations
      for i in range(len(fixed_stack)):
        print("fixed_stack i:",i,"//",fixed_stack[i])
        for j in range(len(temp_stack)):
          print("temp_stack j:",j,"//",temp_stack[j])

          out_list.append(fixed_stack[i] + temp_stack[j])
          tmp_holder.append(fixed_stack[i] + temp_stack[j])
          

  out_list.sort()
  print("\n\nlanguage final list:", out_list) #final list

language("abc", 3)

# ===================== STRETCH =========================
def stretch(in_str, k):
  print("\n==== STRETCH =====")
  out_list = []

  #base case
  if k != 0:
    temp_stack = []
    fixed_stack = []

    out_string = ""

    # << INITIALIZE FIXED STACK >>
    # fixed stack should hold all stretches of first char
    for count in range(k): 
      out_string += in_str[0]
      fixed_stack.append(out_string)

    # << RECURSION >>
    # get each char starting at i = 1
    for i in range(1, len(in_str)):
      
      # create new round of combinations
      for j in range(len(fixed_stack)):
        out_string = fixed_stack[j] # set out_string to each index of fixed stack

        # for amount of stretch
        for count in range(k):
          out_string += in_str[i] # add curr i char
          temp_stack.append(out_string) # add to temp stack 

      # save to fixed stack & clear temp stack
      fixed_stack = temp_stack 
      temp_stack = []
      print("fixed stack:", fixed_stack)
      print("temp stack:", temp_stack)

    out_list = fixed_stack
  print("stretch final list:", out_list)

stretch("abc", 2)


def bubble(in_str):
  print("\n==== BUBBLE ====")
  final_output = [in_str]
  fixed_array = final_output

  # 
  for swapcount in range(len(in_str)):
    # for each char in string (except end)
    bubble = list(in_str)
    for c in range(swapcount):
      # swap
      tmp = bubble[c]
      bubble[c] = bubble[c+1]
      bubble[c+1] = tmp
  
    bubble = ''.join(bubble) # change list to string
  
    # check if bubble is in array already
    final_output.append(bubble)
    print("FINAL:", final_output)

        
        # TODO: save findings in temp array, iterate upon those
        
  print("final output:", final_output)
  
#bubble("abc")