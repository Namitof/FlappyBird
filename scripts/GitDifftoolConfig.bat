@echo off
git config diff.tool p4merge
git config --get diff.tool
echo p4merge difftool configurado correctamente
pause