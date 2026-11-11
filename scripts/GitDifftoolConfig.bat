@echo off
git config --global diff.tool p4merge
git config --global --get diff.tool
echo p4merge difftool configurado correctamente
pause