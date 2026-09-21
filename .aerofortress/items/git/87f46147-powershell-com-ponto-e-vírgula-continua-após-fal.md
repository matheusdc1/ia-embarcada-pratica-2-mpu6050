---
id: 87f46147-75e9-464f-b868-6013185ae5e2
slug: git
type: scar
title: PowerShell com ponto e vírgula continua após falha de validação
tags: git, powershell, validation
provenance: observado
evidence: commit ee539c6 no workspace tarefa
decay: stable
created: 2026-09-21T22:01:12.539864600+00:00
updated: 2026-09-21T22:01:12.539864600+00:00
validated: 2026-09-21T22:01:12.539864600+00:00
links:
---

Ao encadear `git diff --cached --check; git commit`, o PowerShell executa o commit mesmo quando a verificação retorna erro. Para gates antes de commit, interrompa explicitamente quando `$LASTEXITCODE -ne 0` antes de chamar `git commit`; não use apenas ponto e vírgula.
