##################
# COMMAND PROMPT #
##################

function exitstatus {

    EXITSTATUS="$?"
    BOLD="\[\033[1m\]"
    RED="\[\033[1;31m\]"
    GREEN="\[\e[32;1m\]"
    BLUE="\[\e[34;1m\]"
    OFF="\[\033[m\]"

    PROMPT="\[\033[35m\]\t${OFF}-\[\033[36m\]\u${OFF}@\[\033[32m\]\h:\[\033[33;1m\]\w${OFF}"

    if [ "${EXITSTATUS}" -eq 0 ]
    then
       PS1="${PROMPT} ${BOLD}${GREEN}\$ ${OFF}"
    else
       PS1="${PROMPT} ${BOLD}${RED}\$ ${OFF} "
    fi

    PS2="${BOLD}>${OFF} "
}

PROMPT_COMMAND=exitstatus

################
#   ALIASES    #
################

# LS
export CLICOLOR=1
export LSCOLORS=ExFxBxDxCxegedabagacad
alias ls='ls -GFh'
alias ll='ls -GFhla'

# HISTORY
alias hy="history"

# RM
alias rm='rm -i'

# CAT
# alias ccat='pygmentize -g'
alias c='pygmentize -g -O style=colorful,linenos=1'
# alias c='pygmentize -g'

# THEFUCK
#eval $(thefuck --alias)

# ANTLR v4
alias antlr4='java -jar /usr/local/lib/antlr-4.7-complete.jar'
alias grun='java org.antlr.v4.gui.TestRig'

# FINDER
alias showFiles='defaults write com.apple.finder AppleShowAllFiles YES; killall Finder /System/Library/CoreServices/Finder.app'
alias hideFiles='defaults write com.apple.finder AppleShowAllFiles NO; killall Finder /System/Library/CoreServices/Finder.app'

# DATE
alias date='date "+%H:%M:%S   %d/%m/%y"'

# python -m markdown notes.md > notes.html
alias markdown='python -m markdown'

# MySQL Server
alias mysql='/usr/local/mysql/bin/mysql'


#########################
# ENVIRONMENT VARIABLES #
#########################

##
# Your previous /Users/hg/.bash_profile file was backed up as /Users/hg/.bash_profile.macports-saved_2017-04-10_at_13:58:25
##

# MacPorts Installer addition on 2017-04-10_at_13:58:25: adding an appropriate PATH variable for use with MacPorts.
export PATH="/opt/local/bin:/opt/local/sbin:$PATH"
# Finished adapting your PATH environment variable for use with MacPorts.




# TO BE DELETED
# Add environment variable COCOS_CONSOLE_ROOT for cocos2d-x
export COCOS_CONSOLE_ROOT=/Users/hg/Downloads/cocos2d-x-3.15.1/tools/cocos2d-console/bin
export PATH=$COCOS_CONSOLE_ROOT:$PATH

# Add environment variable COCOS_X_ROOT for cocos2d-x
export COCOS_X_ROOT=/Users/hg/Downloads
export PATH=$COCOS_X_ROOT:$PATH

# Add environment variable COCOS_TEMPLATES_ROOT for cocos2d-x
export COCOS_TEMPLATES_ROOT=/Users/hg/Downloads/cocos2d-x-3.15.1/templates
export PATH=$COCOS_TEMPLATES_ROOT:$PATH
