# completion script for make.sh script

compdef _make.sh make.sh
compdef _make.sh zmake

function _make.sh {

  local -a subcommands

  subcommands=(
	'release:build static library'
	'install:install static library'
	'test:build test executable'
	'rm:remove build files'
  )

  local -a options
  options=(
	'--help:print this help'
	'--version:print version'
  )

  _arguments \
	'1: :->level1' \
	'*:: :->other' \

  case $state in
	level1)
	  _describe -t commands 'subcommands' subcommands && ret=0
	  _describe -t options 'program options' options && ret=0
	  ;;
	other)
	  _files
	  ;;
  esac

  return ret
}


