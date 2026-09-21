---
id: 4fba90fa-7f39-476e-ae92-a5c75130af63
slug: git
type: scar
title: Queda de energia pode zerar índice e referência da branch no Git
tags: git, recuperacao, queda-de-energia
provenance: observado
evidence: .git/recovery-power-loss; commit recuperado 6c9e2b251a636b527d3aa1847d7d37052f7a6346
decay: stable
created: 2026-09-21T22:21:58.380245400+00:00
updated: 2026-09-21T22:21:58.380245400+00:00
validated: 2026-09-21T22:21:58.380245400+00:00
links:
---

Após uma queda de energia, `.git/index` apresentou `bad signature` e `.git/refs/heads/main` continha apenas bytes NUL. O commit mais recente ainda existia como objeto órfão. Para recuperar sem perder trabalho: preserve os arquivos corrompidos fora de `refs/`, identifique o commit correto com reflog/`git fsck`/`git show`, restaure a referência com `git update-ref`, reconstrua o índice com `git reset --mixed <commit>` e confirme com `git status` e `git fsck`. Nunca use `reset --hard` nessa recuperação.
