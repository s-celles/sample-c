# -*- mode: ruby -*-
# vi: set ft=ruby :
#
# Isolation Notes:
# - Vagrant/VirtualBox provides high isolation (full VM with separate kernel)
# - However, the synced_folder below mounts the host project directory
# - For true isolation, remove the synced_folder and copy files instead
# - This setup is suitable for development, not for running untrusted code

Vagrant.configure("2") do |config|
  # Ubuntu 24.04 LTS (Noble Numbat)
  config.vm.box = "bento/ubuntu-24.04"

  config.vm.hostname = "sample-c-dev"

  # VirtualBox provider settings
  config.vm.provider "virtualbox" do |vb|
    vb.name = "sample-c-vagrant"
    vb.memory = "2048"
    vb.cpus = 2
  end

  # Sync project folder
  config.vm.synced_folder ".", "/home/vagrant/project"

  # Provision: install build tools
  config.vm.provision "shell", inline: <<-SHELL
    apt-get update
    apt-get install -y \
      build-essential \
      cmake \
      git \
      curl
  SHELL

  # Build project on first boot
  config.vm.provision "shell", privileged: false, inline: <<-SHELL
    cd /home/vagrant/project
    cmake -B build -S .
    cmake --build build
    echo "Build complete! Run: ./build/HelloWorld"
  SHELL
end
